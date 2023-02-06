let task = -1;
while(task != "0")
{
    task = prompt("Введите номер задания");
    switch(Number(task))
    {
        case 1:
            {
                

                let masOfWords = prompt("Enter comment");
                masOfWords = masOfWords.split(" ");
                for (let i = 0; i < masOfWords.length; i++)
                {
                    if (masOfWords[i].indexOf("кот") != -1)
                    {
                        let indexOfCat = masOfWords[i].indexOf("кот");
                        let newString = masOfWords[i].slice(0, indexOfCat) + "*" + masOfWords[i].slice(indexOfCat + 3);
                        masOfWords[i] = newString;
                    }
                    if (masOfWords[i].indexOf("собак") != -1)
                    {
                        let newString = masOfWords[i][0].toUpperCase() + masOfWords[i].slice(1);
                        masOfWords[i] = newString;
                    }
                }
                for (let i = 0; i < masOfWords.length; i++)
                {
                    if (masOfWords[i] == "пёс")
                    {
                        masOfWords.splice(i, 0, "многоуважаемый");
                        i++;
                    }
                }
                let stringOut = masOfWords.join(" ");
                alert(stringOut);
                break;
            }
        case 2:
            {
                let userInput = Number(prompt("Enter number of day"));
                if (userInput != NaN || userInput > 0 || userInput < 7 || userInput.isInteger())
                {
                    let strDay = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"];
                    let dayObject = {
                        number: userInput,
                        nameDay: strDay[userInput - 1],
                    }
                    alert(`It's ${dayObject.nameDay}, the number is ${dayObject.number}`);
                    let numberOfOddsOrEvensDunno = 0;
                    for (let i = 0; i < 7; i++)
                    {
                        if ((i + 1) % 2 == 1)
                        {
                            alert(`It's ${strDay[i]}, the number is ${i + 1}`);
                            numberOfOddsOrEvensDunno++;
                        }
                    }
                }
                else
                {
                    alert("Invalid number")
                }
                break;
            }
        case 3:
            {
                break;
            }
        case 4:
            {
                let bin = new Set();
                let good = -1;
                let choice = -1
                while (true)
                {
                    choice = prompt("Введите 1, чтобы добавить в корзину, 2, чтобы удалить из корзины, 3, чтобы проверить наличие в корзине");
                    if (choice == 0) break;
                    good = prompt("Введите номер товара");
                    switch(Number(choice))
                    {
                        case 1:
                        {
                            bin.add(good);
                            break;
                        }
                        case 2:
                        {
                            bin.delete(good);
                            break;
                        }
                        case 3:
                        {
                            if (bin.has(good)) alert("Есть такой товар");
                            else alert("Нет такого товара");
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    alert(`В корзине ${bin.size} товаров`);
                }
                break;
            }
        case 5:
            {
                let map = new Map()
                let data = [12, 23, 34, 45, 56, 67, 78, 89, 90, 101];
                let choice = -1;
                let good = -1;
                while (true)
                {
                    choice = prompt("Введите 1, чтобы добавить в корзину, 2, чтобы удалить из корзины, 3, чтобы изменить количество");
                    if (choice == 0) break;
                    good = prompt("Введите номер товара");
                    if (!(1 <= good <= 10))
                    {
                        alert("Invalid");
                        break;
                    }
                    switch(Number(choice))
                    {
                        case 1:
                        {
                            let amount = prompt("Введите количество добавляемого товара");
                            map.set(good, [amount, data[good - 1]]);
                            break;
                        }
                        case 2:
                        {
                            if (map.delete(good)) alert("Товар успешно удалён");
                            else alert("Товар был безуспешно удалён, потому что его там и не было");
                            break;
                        }
                        case 3:
                        {
                            if (map.has(Number(good)))
                            {
                                let newAmount = prompt("Введите новое количество товара");
                                if (newAmount > 0)
                                {
                                    map.set(good, [newAmount, data[good - 1]]);
                                }
                                else
                                {
                                    alert("Количество товара должно быть положительным");
                                }
                            }
                            else
                            {
                                alert("Такого товара нет");
                            }
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                    let allMap = "";
                    let totalCost = 0;
                    let amount = 0;
                    for (let entry of map)
                    {
                        allMap += entry + "\n";
                    }
                    for (let i = 0; i < data.length; i++)
                    {
                        if (map.has(String(i + 1)))
                        {
                            totalCost += map.get(String(i + 1))[0] * map.get(String(i + 1))[1];
                            amount++;
                        }
                    }
                    allMap += "сумма: " + totalCost + "\nколичество: " + amount;
                    alert(allMap);
                }
                break;
            }
    }
}
let task3 = function()
{
    let accObj = {
        backgroundColor: "yellow",
    }
    let refObj = {
        fontSize: "20px",
        fontFamily: "Consolas",
        color: "red",
    }
    let bttObj = {
        width: "120px",
        height: "100px",
        backgroundColor: "red",
        color: "green",
    }
    let buttons = document.querySelectorAll("button");
    for (let i = 0; i < buttons.length; i++)
    {
        //buttons[i].style.backgroundColor = bttObj.backgroundColor;
        //buttons[i].style.width = bttObj.width;
        //buttons[i].style.height = bttObj.height;
        //buttons[i].style.color = bttObj.color;
        Object.assign(buttons[i].style, bttObj);
        if (i == 0)
        {
            buttons[i].style.backgroundColor = accObj.backgroundColor;
        }
    }
    let references = document.querySelectorAll(".reference");
    for (let i = 0; i < references.length; i++)
    {
        //references[i].style.fontFamily = refObj.fontFamily;
        //references[i].style.fontSize = refObj.fontSize;
        //references[i].style.color = refObj.color;
        Object.assign(references[i].style, refObj);
        if (i == 1)
        {
            references[i].style.backgroundColor = accObj.backgroundColor;
        }
    }    
}
document.addEventListener("DOMContentLoaded", task3);