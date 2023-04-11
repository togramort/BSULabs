const path = require('path');
const express = require('express'); //include
const app = express(); //create

app.use(express.static(path.resolve(__dirname, 'dist')));

app.get('/open', (req, res) => {
    res.sendFile(path.resolve(__dirname, 'src', 'index.html'));
});

app.get('/down', (req, res) => {
    res.download(path.resolve(__dirname, 'files', 'books.json'));
});

app.listen(9999, () => {
    console.log('server on port 9999 :)');
});