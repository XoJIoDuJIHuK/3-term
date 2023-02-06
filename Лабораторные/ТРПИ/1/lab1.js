let task = 0;
while(task != "выход")
{
    task = prompt("Введите номер задания");
    switch(Number(task))
    {
        case 1:
            {
                function pow(x, n)
                {
                    let result = 1;
                    for (let i = 0; i < n; i++) result *= x;
                    return result;
                }
                x = prompt("x?", '');
                n = prompt("n?", '');
                if (n < 0) alert(`Введите положительную степень вместо ${n}`);
                else alert(pow(x, n));
                break;
            }
        case 2:
            {
                let userName = "XoJIoDuJIHuK";
                let city = "Minsk";
                let year = 2004;
                let color = "red";
                let userAnswer = true;
                let inf = Infinity;
                let int = 532;
                let perimeter = "120 mm";
                let userAlert = "Введенные данные неверны";
                break;
            }
        case 3:
            {
                let a = 5; //number
                let name = "Name" //string
                let i = 0; //number
                let double = 0.23; //number
                let result = 1/0; //number
                let answer = true; //boolean
                let no = null; //null (но вообще object)
                break;
            }
        case 4:
            {
                alert(`Площадь равна ${45 * 21}мм`);
                break;
            }
        case 5:
            {
                alert(`Поместится ${Math.floor(45 * 21 / (5 * 5))} квадратов со стороной 5мм`);
                break;
            }
        case 6:
            {
                let ii = 2;
                let aa = ++ii;
                let bb = ii++;
                if (aa == bb) result = '=';
                else if (aa < bb) result = '<';
                else result = '>';
                alert(`a ${result} b`);
                //но вообще а равно б, так как значение i присваивается а после инкрементирования, а б - до
                break;
            }
        case 7:
            {
                function cmp(aa, bb)
                {
                    if (aa == bb) result = '=';
                    else if (aa < bb) result = '<';
                    else if (aa > bb) result = '>';
                    else
                    {
                        alert("¯\\_(ツ)_/¯");
                        return;
                    }
                    alert(`${aa} ${result} ${bb}`);
                }
                cmp("Привет", "привет");//<
                cmp("Привет", "пока");//<
                cmp(45, "53");//<
                cmp(false, 3);//<
                cmp(true, "3");//<
                cmp(3, "5мм");//>
                cmp(null, undefined);//=
                break;
            }
        case 8:
            {
                alert("Введённые пользователем данные неверны");
                break;
            }
        case 9:
            {
                answer = prompt("Введите ответ на секретный вопрос");
                break;
            }
        case 10:
            {
                userName = prompt("Enter username");
                let password = prompt("Enter password");
                if (userName == "XoJIoDuJIHuK" && password == "123") alert("Welcome");
                else alert("Invalid data");
                break;
            }
        case 11:
            {
                let exams;
                for (let i = 0; i < 3; i++) exams[i] = prompt(`Введите оценку экзамена №${i + 1}`);
                if (exams[0] < 4 && exams[1] < 4 && exams[2] < 4) alert("Отчислен");
                else if (exams[0] < 4 || exams[1] < 4 || exams[2] < 4) alert("Пересдача");
                else alert("Переведён");
                break;
            }
        case 12:
            {
                a = Number(prompt("Enter a"));
                b = Number(prompt("Enter b"));
                alert(a + b);
                break;
            }
        case 13:
            {
                alert(true + true);
                alert(0 + "5");
                alert(5 + "мм");
                alert(8 / Infinity);
                alert(9 * "\n9");
                alert(null - 1);
                alert("5" - 2);
                alert("5px" - 3);
                alert(true - 3);
                alert(7 || 0);
                break;
            }
        case 14:
            {
                let numbers = [];
                for (let i = 1; i <= 10; i++) alert(numbers[i] = i % 2 ? i + "мм" : i + 2);
                break;
            }
        case 15:
            {
                let input = 0;
                while(input < 100) input = prompt();
                break;
            }
        case 16:
            {
                let days = ["пн", "вт", "ср", "чт", "пт", "сб", "вс"];
                alert(days[prompt("Введите номер дня") - 1]);
                break;
            }
        default: break;
    }
}