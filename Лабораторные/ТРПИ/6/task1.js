let obj = []

obj[0] = {
    shape: "square",
    color: "yellow",
    lines: 0,
    size: "big",
}

obj[1] = {
    shape: "circle",
    color: "",
    lines: 0,
    size: "big",
}

obj[2] = {
    shape: "triangle",
    color: "",
    lines: 1,
    size: "big",
}

obj[3] = {
    shape: "square",
    color: "yellow",
    lines: 0,
    size: "small",
}

obj[4] = {
    shape: "circle",
    color: "green",
    lines: 0,
    size: "big",
}

obj[5] = {
    shape: "triangle",
    color: "",
    lines: 3,
    size: "big",
}

let greenCircleProperties = Object.keys(obj[4]);
let greenValues = greenCircleProperties.map((key) => obj[4][key]);
let map = greenCircleProperties.map(() => true);
 for (let i = 0; i < greenCircleProperties.length; i++)
 {
    for (let j = 0; j < obj.length; j++)
    {
        if (j == 4) continue;
        let properties = Object.keys(obj[j]);
        for (let k = 0; k < properties.length; k++)
        {
            if (obj[j][properties[k]] == obj[4][greenCircleProperties[k]]) map[i] = false;
        }
    }
 }

 console.log("Start свойства, которые отличают фигуру «зеленый круг»");
 for (let i = 0; i < map.length; i++)
 {
    if (map[i]) console.log(greenCircleProperties[i]);
 }
 console.log("End свойства, которые отличают фигуру «зеленый круг»");

 console.log("свойства, которые описывают фигуру «треугольник с тремя линиями»");
 console.log(Object.keys(obj[5]));

 console.log("есть ли у фигуры «маленький квадрат» собственное свойство, которое определяет цвет фигуры.");
 console.log(Object.keys(obj[3]).includes("color"));