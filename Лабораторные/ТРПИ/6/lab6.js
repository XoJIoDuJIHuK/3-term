let ArrayOfProducts = [];
class Button {
    width = "0px";
    heinght = "0px";
    text = "";
    constructor(w, h, t)
    {
        this.width = w;
        this.height = h;
        this.text = t;
    }
    static Add(obj, button)
    {
        obj.button = button;
    }
    static Delete(obj)
    {
        obj.button = undefined;
    }
}
class Product {
    backgroundColor = "white";
    backgroundImage = "";
    name = "";
    price = 0;
    button = undefined;
    constructor(path, n, p, button)
    {
        this.backgroundImage = path;
        this.name = n;
        this.price = p;
        this.button = button;
    }
    static Add(product)
    {
        ArrayOfProducts.push(product);
        UpdateDocument();
    }
    static Delete(_name)
    {
        let index = ArrayOfProducts.findIndex(item => item.name == _name);
        if (index != -1) ArrayOfProducts.splice(index, 1);
        else alert("Such element doesn't exist");
        UpdateDocument();
    }
};
function UpdateDocument()
{
    let numOfLines = Math.ceil(ArrayOfProducts.length / 4);
    let root = document.getElementById("catalogue");
    root.innerHTML = "";
    for (let i = 0; i < numOfLines; i++)
    {
        let line = document.createElement("div");
        line.className = "line";
        let itemsInLine = (ArrayOfProducts.length - i * 4) <= 4 ? ArrayOfProducts.length - i * 4 : 4;
        for (let j = 0; j < itemsInLine; j++)
        {
            let obj = ArrayOfProducts[i * 4 + j];
            let good = document.createElement("div");
            good.className = "catalogueItem";
            good.style.backgroundColor = obj.backgroundColor;

            let info = document.createElement("div");
            info.className = "itemInfo";

            let imageWrapper = document.createElement("div");
            imageWrapper.className = "imageWrapper";

            let pic = document.createElement("img");
            pic.className = "itemPicture";
            pic.setAttribute("src", obj.backgroundImage);
            imageWrapper.append(pic);
            info.append(imageWrapper);

            let name = document.createElement("div");
            name.className = "productName";
            name.innerText = obj.name;
            info.append(name);

            let price = document.createElement("div");
            price.className = "itemPrice";
            price.innerText = obj.price;
            info.append(price);

            good.append(info);

            let buttonWrapper = document.createElement("div");
            buttonWrapper.className = "buttonWrapper";

            let button = document.createElement("button");
            button.innerText = obj.button.text;
            button.setAttribute("style", `width:${obj.button.width};height:${obj.button.height}`);
            buttonWrapper.append(button);
            good.append(buttonWrapper);

            line.append(good);
        }
        root.append(line);
    }
};
function GetRandomInteger(min, max)
{
    return Math.round(Math.random() * (max - min) + min);
}

let vendors = ["Lenovo", "Apple", "MSI", "HP", "Acer", "ASUS"];
let models = ["Legion", "IdeaPad", "Notebook", "Gaming Laptop", "Workstation"];

function Start()
{
    let input = "";
    for (let i = 0; i < 15; i++)
    {
        let model = vendors[GetRandomInteger(0, 5)] + ' ' + models[GetRandomInteger(0, 4)];
        Product.Add(new Product(`img/${GetRandomInteger(1, 2)}.png`, model, `$${GetRandomInteger(500, 5000)}`, new Button("50%", "30px", "Add to cart")));
    }

    for (let i = 0; i < ArrayOfProducts.length; i++)
    {
        if (i % 2 == 1)
        {
            ArrayOfProducts[i].backgroundColor = "gray";
        }
    }
    
    Product.Delete(ArrayOfProducts[GetRandomInteger(0, ArrayOfProducts.length - 1)].name);
    UpdateDocument();

    while (0)
    {
        input = prompt("1 - add, 2 - delete, 3 - edit");
        switch (input)
        {
            case "1":
            {
                let params = prompt("enter [path name price width height text] to add").split(' ');
                Product.Add(new Product(params[0], params[1], params[2], new Button(params[3], params[4], params[5])));
                break;
            }
            case "2":
            {
                let name = prompt("Enter name to delete");
                Product.Delete(name);
                break;
            }
            case "3":
            {
                let name = prompt("Enter name to edit");
                let object = ArrayOfProducts[ArrayOfProducts.findIndex(item => item.name == name)];
                let params = prompt("enter [path name price width height text] to edit").split(' ');
                object.path = params[0];
                object.name = params[1];
                object.price = params[2];
                object.button.width = params[3];
                object.button.height = params[4];
                object.button.text = params[5];
                break;
            }
            default: return;
        }
    }
}

setTimeout(Start, 1000);