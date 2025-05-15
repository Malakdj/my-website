const express = require("express");
const { exec } = require("child_process");
const fs = require("fs");
const path = require("path");

const app = express();
app.use(express.json());
app.use(express.static(path.join(__dirname, "pages"))); 

const codesDir = path.join(__dirname, "codes"); 

const executeCipher = (algorithm, isDecryption, key, message, rotateInterval, res) => {
    const suffix = isDecryption ? "_decrypt" : "";
    const normalizedName = algorithm.replace(/è/g, 'e'); 
    const cppFile = path.join(codesDir, `${normalizedName}${suffix}.cpp`);
    
    if (!fs.existsSync(cppFile)) {
        return res.status(400).send(`Error: ${algorithm}${suffix}.cpp not found.`);
    }

    let inputData = key;
    if (algorithm === "Alberti") {
        inputData += `\n${rotateInterval}`;
    }
    inputData += `\n${message}`;
    
    fs.writeFileSync("input.txt", inputData);
    
    const exeFile = path.join(codesDir, `${algorithm}${suffix}.exe`);
    const command = `g++ \"${cppFile}\" -o \"${exeFile}\" && \"${exeFile}\"`;
    
    exec(command, (error, stdout, stderr) => {
        if (error) {
            res.send("Error: " + stderr);
        } else {
            res.send(stdout);
        }
    });
};

const port = process.env.PORT || 3000;  

app.post("/run", (req, res) => {
    const { algorithm, key, message, rotateInterval } = req.body;
    console.log(`Encryption request for ${algorithm} with key ${key}`);
    
    executeCipher(algorithm, false, key, message, rotateInterval, res);
});

app.post("/runDecryption", (req, res) => {
    const { algorithm, key, message, rotateInterval } = req.body;
    console.log(`Decryption request for ${algorithm} with key ${key}`);
    
    executeCipher(algorithm, true, key, message, rotateInterval, res);
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
