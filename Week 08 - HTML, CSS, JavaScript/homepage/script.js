let buttons = document.querySelectorAll("button");
for (let i = 0; i < buttons.length; i++) {
    buttons[i].addEventListener('click', function() {
        if (buttons[i].innerHTML === "About me") {
            window.location.href = "https://expert-tribble-r4w75469jvx9cg5p-8080.app.github.dev/aboutme.html";
        }
        else if (buttons[i].innerHTML === "My favourite hobbie") {
            window.location.href = "https://expert-tribble-r4w75469jvx9cg5p-8080.app.github.dev/favhobbie.html";
        }
        else if (buttons[i].innerHTML === "Thank you") {
            window.location.href = "https://expert-tribble-r4w75469jvx9cg5p-8080.app.github.dev/thankyou.html";
        }
        else if (buttons[i].innerHTML === "Homepage") {
            window.location.href = "https://expert-tribble-r4w75469jvx9cg5p-8080.app.github.dev/index.html";
        }
    })
}
