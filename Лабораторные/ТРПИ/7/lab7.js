document.addEventListener("DOMContentLoaded", Start);

function sleep(milliseconds) {
    const date = Date.now();
    let currentDate = null;
    do {
      currentDate = Date.now();
    } while (currentDate - date < milliseconds);
  }  

function Start()
{
    let redLineOy = parseFloat(getComputedStyle(document.querySelector(".redLine")).top + 
                               getComputedStyle(document.querySelector(".redLine")).height);
    let ball = document.querySelector(".ball");
    let i1 = document.querySelector(".i1");
    let i2 = document.querySelector(".i2");

    let fromX, fromY, toX, toY;

    let Timing = function(timeFraction)
    {
        return Math.pow(timeFraction, 1 / 8);
    }

    let Draw = function(progress)
    {
        console.log(`progress: ${progress}`);
        ball.style.top = Math.round((toY - fromY) * progress + fromY) + 'px';
        ball.style.left = Math.round((toX - fromX) * progress + fromX) + 'px';
    }

    ball.onmousedown = function(event) {

        ballPressed = true;
        let shiftX = event.clientX - ball.getBoundingClientRect().left;
        let shiftY = event.clientY - ball.getBoundingClientRect().top;

        function onMouseMove(event) {
            moveAt(event.pageX, event.pageY);
        }
    
        function moveAt(pageX, pageY) {
            ball.style.left = pageX - shiftX + 'px';
            if (pageY - shiftY >= +redLineOy) ball.style.top = pageY - shiftY + 'px';
            else ball.style.top = redLineOy + 'px';
        }
      
        document.addEventListener('mousemove', onMouseMove);
      
        ball.style.position = 'absolute';
        ball.style.zIndex = 10000;
      
        moveAt(event.pageX, event.pageY);

        ball.onmouseup = function() {
            document.removeEventListener('mousemove', onMouseMove);
            ball.onmouseup = null;
            toX = parseFloat(getComputedStyle(document.querySelector(".redLine")).width) - 
                  parseFloat(ball.style.left);
            toY = redLineOy * 2 - parseFloat(ball.style.top);
            fromX = parseFloat(ball.style.left);
            fromY = parseFloat(ball.style.top);

            function animate({timing, draw, duration}) {

                let start = performance.now();
              
                requestAnimationFrame(function animate(time) {
                  // timeFraction изменяется от 0 до 1
                  let timeFraction = (time - start) / duration;
                  if (timeFraction > 1) timeFraction = 1;
              
                  // вычисление текущего состояния анимации
                  let progress = timing(timeFraction);
              
                  draw(progress); // отрисовать её
              
                  if (timeFraction < 1) {
                    requestAnimationFrame(animate);
                  }
              
                });
            }
            animate({
                timing: Timing,
                draw: Draw,
                duration: 1000
            });
        };
    };
      
    ball.ondragstart = function() {
        return false;
    };
}