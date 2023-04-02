const books = [
    {ID: 1, name: 'Harry Potter', author: 'J.K.Rowling', instances: '3'},
    {ID: 2, name: 'Winnie-the-Pooh', author: 'Alan Alexander Milne', instances: '2'},
    {ID: 3, name: 'Jeeves and Wooster stories', author: 'P.G.Wodehouse', instances: '5'},
    {ID: 4, name: 'Harry Potter and the Philosopher’s Stone', author: 'J.K.Rowling', instances: '10'},
    {ID: 5, name: 'Airport', author: 'Arthur Hailey', instances: '2'}
]

//let booksHead = ['ID', 'name', 'author', 'number of instances'];
const booksHead = Object.keys(books[0]);

const getAvailabilityOfBookForm = {
    label: "label", 
    labelFor: "bookName", 
    labelText: "enter the name of the book:",
    inputText: "input", 
    inputTextType: "text", 
    inputTextId: "bookName",
    inputButton: "input", 
    inputButtonType: "button", 
    inputButtonId: "search", 
    inputButtonValue: "search", 
    inputButtonFunc: "showAvailabilityOfBook()"
}

const getBooksOfAuthorForm = {
    label: "label", 
    labelFor: "authorName", 
    labelText: "enter the name or surname of the author:",
    inputText: "input", 
    inputTextType: "text", 
    inputTextId: "authorName",
    inputButton: "input", 
    inputButtonType: "button", 
    inputButtonId: "search", 
    inputButtonValue: "search", 
    inputButtonFunc: "showbooksOfAuthor()"
}

const getFindBookForm = {
    label: "label", 
    labelFor: "findBook", 
    labelText: "enter the name of the book:",
    inputText: "input", 
    inputTextType: "text", 
    inputTextId: "findBook",
    inputButton: "input", 
    inputButtonType: "button", 
    inputButtonId: "search", 
    inputButtonValue: "search", 
    inputButtonFunc: "showFindBook()"
}

const getDeleteForm = {
    label: "label",
    labelFor: "deleteBook",
    labelText: "delete book by id",
    inputText: "input", 
    inputTextType: "number",
    inputTextId: "deleteBook",
    inputTextMin: "1", 
    inputTextMax: books.length,
    inputButton: "input", 
    inputButtonType: "button", 
    inputButtonId: "delete", 
    inputButtonValue: "delete",
    inputButtonFunc: "deleteBookById()"
}

const getAddForm = {
    label: "label",
    labelFor: "addBook",
    labelText: "add book",
    inputButton: "input", 
    inputButtonType: "button", 
    inputButtonId: "add", 
    inputButtonValue: "add",
    inputButtonFunc: "addBook()"
}

const getKeysForm = {
    label: "label",
    labelFor: "getKeys",
    labelText: "get keys from local storage",
    inputButton: "input", 
    inputButtonType: "button", 
    inputButtonId: "getKeys", 
    inputButtonValue: "get",
    inputButtonFunc: "getKeysFromLS()"
}

const getIDForm = {
    label: "label",
    labelFor: "getID",
    labelText: "enter the ID of the book",
    inputText: "input", 
    inputTextType: "number",
    inputTextId: "getID",
    inputTextMin: books.length + 1,
    inputTextMax: books.length + 1
}

const getNameForm = {
    label: "label",
    labelFor: "getName",
    labelText: "enter the name of the book",
    inputText: "input", 
    inputTextType: "text",
    inputTextId: "getName"
}

const getAuthorForm = {
    label: "label",
    labelFor: "getAuthor",
    labelText: "enter the author of the book",
    inputText: "input", 
    inputTextType: "text",
    inputTextId: "getAuthor"
}

const getInstancesForm = {
    label: "label",
    labelFor: "getInstances",
    labelText: "enter the instances of the book",
    inputText: "input", 
    inputTextType: "number",
    inputTextId: "getInstances",
    inputTextMin: "1",
    inputButton: "input", 
    inputButtonType: "button", 
    inputButtonId: "addBook", 
    inputButtonValue: "add",
    inputButtonFunc: "addBookToLS()"
}

localStorage.setItem("allBooksInLib", JSON.stringify(books));
localStorage.setItem("formGetAvailabilityOfBook", JSON.stringify(getAvailabilityOfBookForm));
localStorage.setItem("formGetBooksOfAuthor", JSON.stringify(getBooksOfAuthorForm));
localStorage.setItem("formGetFindBook", JSON.stringify(getFindBookForm));
localStorage.setItem("formGetDelete", JSON.stringify(getDeleteForm));
localStorage.setItem("formGetAdd", JSON.stringify(getAddForm));
localStorage.setItem("formGetKeys", JSON.stringify(getKeysForm));
localStorage.setItem("formGetID", JSON.stringify(getIDForm));
localStorage.setItem("formGetName", JSON.stringify(getNameForm));
localStorage.setItem("formGetAuthor", JSON.stringify(getAuthorForm));
localStorage.setItem("formGetInstances", JSON.stringify(getInstancesForm));

function availabilityOfBook(){
    window.open("availabilityOfBook.html","_self");
}

function booksOfAuthor(){
    window.open("booksOfAuthor.html","_self");
}

function findBook(){
    window.open("findBook.html","_self");
}

function allBooks(){
    window.open("allBooks.html","_self");
}

function additionals() {
    window.open("additionals.html", "_self");
}

function addBook() {
    window.open("addBook.html", "_self");
}

function generateTable(arrayHead, array){
    var temp = document.getElementById("table");
    if (temp != null) {
        temp.parentNode.removeChild(temp);
    }
    if (array.length === 0) {
        alert("nothing to show");
        return false;
    }
    var table = document.createElement('table');
    table.setAttribute("id", "table");
    var tableHead = document.createElement('thead');
    var tableBody = document.createElement('tbody');
    table.appendChild(tableHead);

    for (var i = 0; i < arrayHead.length; ++i) {
        tableHead.appendChild(document.createElement("th")).appendChild(document.createTextNode(arrayHead[i]));
    }

    array.forEach(function(rowData) {
    var row = document.createElement('tr');

        rowData.forEach(function(cellData) {
            var cell = document.createElement('td');
            cell.appendChild(document.createTextNode(cellData));
            row.appendChild(cell);
        });

    tableBody.appendChild(row);
    });

  table.appendChild(tableBody);
  document.body.appendChild(table);
}

function generateForm(itemInStorage){
    var form = document.querySelector('form');
    let lineBreak = document.createElement('br');
    var getItem = JSON.parse(localStorage.getItem(itemInStorage));
    //for (let i = 0; i < getItem.length; ++i) {
    if (getItem.label == "label") {
        let label = document.createElement(getItem.label);
        label.setAttribute("for", getItem.labelFor);
        label.innerHTML = getItem.labelText;
        form.append(label);
        form.appendChild(lineBreak.cloneNode());
    }
    if (getItem.inputText == "input") {
        let input = document.createElement(getItem.inputText);
        input.setAttribute("type", getItem.inputTextType);
        input.setAttribute("id", getItem.inputTextId);
        if (getItem.inputTextMin) {
            input.setAttribute("min", getItem.inputTextMin);
        }
        if (getItem.inputTextMax) {
            input.setAttribute("max", getItem.inputTextMax);
        }
        form.append(input);
        form.appendChild(lineBreak.cloneNode());
        form.appendChild(lineBreak.cloneNode());
    }
    if (getItem.inputButton == "input") {
        let input = document.createElement(getItem.inputButton);
        input.setAttribute("type", getItem.inputButtonType);
        input.setAttribute("id", getItem.inputButtonId);
        input.setAttribute("value", getItem.inputButtonValue);
        input.setAttribute("onclick", getItem.inputButtonFunc);
        form.append(input);
        form.appendChild(lineBreak.cloneNode());
        form.appendChild(lineBreak.cloneNode());
        form.appendChild(lineBreak.cloneNode());
    }
}

function validate(text){
    if (text == "") {
        alert("field must not be empty");
        return false;
    } else if (!isNaN(text)) {
        alert("you must enter a text not a number");
        return false;
    } else {
        return true;
    }
}

function showAvailabilityOfBook(){
    let neededInfo = []
    let bookName = document.getElementById("bookName").value;
    if (!validate(bookName)) {
        return false;
    }
    
    var booksFromLocal = JSON.parse(localStorage.getItem('allBooksInLib'));
    for (let i = 0; i < books.length; ++i){
        if (booksFromLocal[i].name.toLowerCase().includes(bookName.toLowerCase())) {
            neededInfo.push([booksFromLocal[i].name, booksFromLocal[i].author, booksFromLocal[i].instances]);
        }
    }

    let neededInfoHead = []
    for (let i = 1; i < booksHead.length; ++i){
        neededInfoHead.push(booksHead[i]);
    }

    generateTable(neededInfoHead, neededInfo);
}

function showbooksOfAuthor(){
    let neededInfo = []
    let authorName = document.getElementById("authorName").value;
    if (!validate(authorName)) {
        return false;
    }
    
    var booksFromLocal = JSON.parse(localStorage.getItem('allBooksInLib'));
    for (let i = 0; i < books.length; ++i){
        if (booksFromLocal[i].author.toLowerCase().includes(authorName.toLowerCase())) {
            neededInfo.push([booksFromLocal[i].name, booksFromLocal[i].author]);
        }
    }

    let neededInfoHead = []
    for (let i = 1; i < booksHead.length - 1; ++i){
        neededInfoHead.push(booksHead[i]);
    }

    generateTable(neededInfoHead, neededInfo);
}

function showFindBook(){
    let neededInfo = []
    let findBook = document.getElementById("findBook").value;
    if (!validate(findBook)) {
        return false;
    }
    
    var booksFromLocal = JSON.parse(localStorage.getItem('allBooksInLib'));
    for (let i = 0; i < books.length; ++i){
        if (booksFromLocal[i].name.toLowerCase().includes(findBook.toLowerCase())) {
            neededInfo.push([booksFromLocal[i].name, booksFromLocal[i].instances]);
        }
    }

    let neededInfoHead = []
    for (let i = 1; i < booksHead.length; i += 2){
        neededInfoHead.push(booksHead[i]);
    }

    generateTable(neededInfoHead, neededInfo);
}

function showAllBooks(){
    let neededInfo = []
    var booksFromLocal = JSON.parse(localStorage.getItem('allBooksInLib'));
    for (let i = 0; i < books.length; ++i){
        neededInfo.push([booksFromLocal[i].name, booksFromLocal[i].author]);
    }

    let neededInfoHead = []
    for (let i = 1; i < booksHead.length - 1; ++i){
        neededInfoHead.push(booksHead[i]);
    }

    generateTable(neededInfoHead, neededInfo);
}

function addBookToLS() {
    let ID = document.getElementById("getID").valueAsNumber;
    let name = document.getElementById("getName").value;
    let author = document.getElementById("getAuthor").value;
    let instances = document.getElementById("getInstances").value;
    var newobj = booksHead;
    newobj = {
        ID,
        name,
        author,
        instances
    }
    books.push(newobj);
    localStorage.setItem("allBooksInLib", JSON.stringify(books));
}

function deleteBookById() {
    let deleteId = document.getElementById("deleteBook").value;
    var booksFromLocal = JSON.parse(localStorage.getItem('allBooksInLib'));
    booksFromLocal.splice(deleteId - 1, 1);
    localStorage.setItem("allBooksInLib", JSON.stringify(booksFromLocal));
}

function getKeysFromLS() {
    var text = document.createElement('p');
    let lineBreak = document.createElement('br');
    for (var i = 0; i < localStorage.length; ++i) {
        text.append(localStorage.key(i));
        text.appendChild(lineBreak.cloneNode());
    }
    document.body.appendChild(text);
}