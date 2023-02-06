let task = -1;
while(task != "0")
{
    task = prompt("Введите номер задания");
    switch(Number(task))
    {
        case 1:
            {
                let radius = prompt("Введите радиус круга");
                function countDecl(radius)
                {
                    let diameter = radius * 2;
                    let length = 2 * Math.PI * radius;
                    let square = Math.PI * radius ** 2;
                    alert(`Диаметр ${diameter} \nДлина ${length} \nПлощадь ${square}`);
                }
                let countExpr = function(radius)
                {
                    let diameter = radius * 2;
                    let length = 2 * Math.PI * radius;
                    let square = Math.PI * radius ** 2;
                    alert(`Диаметр ${diameter} \nДлина ${length} \nПлощадь ${square}`);
                }
                let countArr = (radius) => {
                    let diameter = radius * 2;
                    let length = 2 * Math.PI * radius;
                    let square = Math.PI * radius ** 2;
                    alert(`Диаметр ${diameter} \nДлина ${length} \nПлощадь ${square}`);
                }
                countArr(radius);
                countExpr(radius);
                break;
            }
        case 2:
            {
                function func2(fstParm = "first", secParm, trdParm)
                {
                    return(String(fstParm) + " " + secParm + " " + trdParm);
                }
                alert(func2(undefined, "second", prompt("Enter third parm")));
                break;
            }
        case 3:
            {
                let numberOfStudents = 0;
                let surname = 0;
                while (surname != "конец")
                {
                    surname = prompt("Enter surname");
                    numberOfStudents++;
                }
                alert(numberOfStudents - 1);
                break;   
            }
        case 4:
            {
                let seconds = Math.pow(26, 5) * Math.pow(10, 3) * 3;
                let secondsInMinute = 60;
                let secondsInHour = 3600;
                let secondsInDay = 3600 * 24;
                let secondsInMonth = secondsInDay * 30;
                let secondsInYear = secondsInMonth * 12;
                let years = Math.floor(seconds / secondsInYear);
                seconds -= years * secondsInYear;
                let months = Math.floor(seconds / secondsInMonth);
                seconds -= months * secondsInMonth;
                let days = Math.floor(seconds / secondsInDay);
                seconds -= days * secondsInDay;
                let hours = Math.floor(seconds / secondsInHour);
                seconds -= hours * secondsInHour;
                let minutes = Math.floor(seconds / secondsInMinute);
                seconds -= minutes * secondsInMinute;
                alert(`${years} лет ${months} месяцев ${days} дней ${hours} часов ${minutes} минут ${seconds} секунд`);
                break;
            }
        case 5:
            {
                let input = prompt("Enter number or string");
                if (!isNaN(Number(input)))
                {
                    let numInput = Number(input);
                    if (Number.isInteger(numInput))
                    {
                        let hexOutput = numInput.toString(16);
                        alert(hexOutput.toUpperCase());
                    }
                    else
                    {
                        alert(`Math.round: ${Math.round(numInput)}`);
                        alert(`Math.ceil: ${Math.ceil(numInput)}`);
                        alert(`Math.floor: ${Math.floor(numInput)}`);
                    }
                }
                else
                {
                    alert(input.toUpperCase());
                    alert(input.toLowerCase());
                }
                break;
            }
        case 6:
            {
                let dicWord = "молоко".toLowerCase();
                let input = prompt("Введите словарное слово").toLowerCase();
                if (input === dicWord)
                {
                    alert("Всё верно");
                }
                else
                {
                    for (let i = 0; i < dicWord.length; i++)
                    {
                        if (dicWord[i] != input[i])
                        {
                            alert(`Ошибка в ${i + 1}-м символе`);
                            break;
                        }
                    }
                }
                break;
            }
        case 7:
            {
                let catA = Number(prompt("Enter A"));
                let catB = Number(prompt("Enter B"));
                let catC = Number(prompt("Enter C"));
                alert(`${catA} ${catB} ${catC}`);
                if (catA == NaN || catB == NaN || catC == NaN)
                {
                    alert("Not numbers");
                }
                else if (catA + catB <= catC || catA + catC <= catB || catB + catC <= catA)
                {
                    alert("Invalid lengths");
                }
                else if (catA <= 0 || catB <= 0 || catC <= 0)
                {
                    alert("Positive lengths only");
                }
                else
                {
                    let per = catA + catB + catC;
                    let halfPer = per / 2;
                    let square = Math.sqrt(halfPer * (halfPer - catA) * (halfPer - catB) * (halfPer - catC));
                    function sin(catB, catC, square)
                    {
                        return(2 * square / catB / catC);
                    }
                    function cos(catA, catB, catC)
                    {
                        return((Math.pow(catB, 2) + Math.pow(catC, 2) - Math.pow(catA, 2)) / (2 * catB * catC));
                    }
                    function tg(catA, catB, catC, square)
                    {
                        return(sin(catB, catC, square) / cos(catA, catB, catC));
                    }
                    function ctg(catA, catB, catC, square)
                    {
                        return(cos(catA, catB, catC) / sin(catB, catC, square));
                    }
                    function height(catA, square)
                    {
                        return(2 * square / catA);
                    }
                    alert(`cosA = ${cos(catA, catB, catC)}`);
                    alert(`sinB = ${sin(catA, catC, square)}`);
                    alert(`tgC = ${tg(catC, catB, catA, square)}`);
                    alert(`ctgA = ${ctg(catA, catB, catC, square)}`);
                    alert(`height B = ${height(catB, square)}`);
                    alert(`perimeter = ${per}`);
                    alert(`square = ${Math.round(square)}`);
                }
                break;
            }
    }
}