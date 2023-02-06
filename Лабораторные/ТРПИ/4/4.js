let task = -1;
while (task != 0)
{
    task = +prompt("Введите номер задания");
    switch(task)
    {
        case 1:
        {
            function noParametersQ(...arguments)
            {
                let L = arguments.length;
                let string = "";
                if (L <= 3)
                {
                    for (let i = 0; i < L; i++)
                    {
                        string = string + arguments[i];
                    }
                }
                else if (3 < L <= 5)
                {
                    for (let i = 0; i < L; i++)
                    {
                        string = string + typeof(arguments[i]);
                    }
                }
                else if (5 < L <= 7)
                {
                    return L;
                }
                else
                {
                    string = "Too many arguments";
                }
                return string;
            }
            noParametersQ();
            noParametersQ(1, 2, "qwerty", 4);
            noParametersQ(1, 2, 3, 4, 5, 6);
            noParametersQ(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);
            break;
        }
        case 5:
        {
            function sum() { alert(s);}
            function makeCounter() { let currentCount = 1; return function() { return currentCount++;}; }
            let functions = [sum, makeCounter];
            for (let i = 0; i < functions.length; i++)
            {
                alert(functions[i].name);
            }
            break;
        }
        case 6:
        {
            function volume(vertex)
            {
                return (x) => {
                    return (y) => {
                        return x * y * vertex;
                    }
                }
            }
            let par1 = volume(3);
            alert(par1(2)(5));
            alert(par1(7)(3));
            break;
        }
        case 7:
        {
            function* generator(direction)
            {
                let directions = [0, 0];
                switch(direction)
                {
                    case "up":
                    {
                        directions[1] = 1;
                        break;
                    }
                    case "down":
                    {
                        directions[1] = -1;
                        break;
                    }
                    case "left":
                    {
                        directions[0] = -1;
                        break;
                    }
                    case "right":
                    {
                        directions[0] = 1;
                        break;
                    }
                }
                for (let i = 1; i <= 10; i++)
                {
                    yield [directions[0] * i, directions[1] * i];
                }
            }
            let object = 
                {
                    Ox: 0,
                    Oy: 0,
                    toString() {
                        return "Ox: " + this.Ox + ", Oy: " + this.Oy;
                    }
                }
            while(true)
            {
                let direction = prompt("Enter direction");
                if (direction == "end") break;
                else
                {
                    let positions = [...generator(direction)];
                    object.Ox += positions[positions.length - 1][0];
                    object.Oy += positions[positions.length - 1][1];
                    alert(object);
                }
            }
        }
    }
}