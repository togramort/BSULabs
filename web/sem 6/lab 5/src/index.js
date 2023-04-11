import './test.js'
import { fromEvent } from 'rxjs'
import { ajax } from 'rxjs/ajax'

console.log("hello from index")

let down = document.getElementById('down');
let del = document.getElementById('del');

let pathDown = 'http://localhost:9999/down';
let file = ajax.getJSON(pathDown);

const clicksDownload = fromEvent(down, 'click');
const clicksDelete = fromEvent(del, 'click');

clicksDownload.subscribe(() => {
    window.open(pathDown, "_self");
    file.subscribe(res => {
        for (var i = 0; i < res.length; ++i) {
            var info = JSON.stringify(res[i]);
            let articleDiv = document.querySelector("div.main");
            var elem = document.createElement("p");
            var text = document.createTextNode(info);
            elem.appendChild(text);
            articleDiv.appendChild(elem);
        }
    });
});

clicksDelete.subscribe(() => {
    let articleDiv = document.querySelector("div.main");
    articleDiv.removeChild(articleDiv.lastElementChild);
});