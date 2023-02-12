
# Arduino Discord.js Car

With an old Arduino car collecting dust in my room, I was eager to turn it into a new and exciting project. The idea of building a custom-build gripper with a camera and sensor mount, controlled by a custom Discord.js bot, sparked my interest as it offered the perfect opportunity to improve my programming skills and explore new tools like Fusion360 for 3D modeling. So, I set out on a mission to create an interactive and fun setup that would not only provide a challenging learning experience but also entertain my friends.
## Features

- Controled throw wifi
- Obstacle avoidance
- Gripper 
- Live camera feed
- Lights

## Tech Stack

- C/C++ (for arduino program)
- JavaScript (for discord bot)
- Fusion360

## Details

At the front of the car, I added a custom gripper that also serves as a GoPro mount, giving a first-person-like view of the car and the gripper's movement. However, after testing the car with these upgrades, I realized that if the car crashed into a wall, it could break. To prevent this, I added two custom ultrasonic sensor mounts at the front, so the car would stop if it detected an obstacle in its way. Additionally, I added a small LED mount that can be attached to the front, making it possible to use the car in the dark.

To make the setup even more fun, I created a small 3D printed cookie with an RFID tag inside, which could be picked up by the gripper and dropped off at an RFID reader connected to an ESP8266. The RFID reader would then send a signal to the Discord bot, letting it know that the cookie has been delivered. The game was to find the cookie and deliver it, and to add a little extra challenge, I turned off the lights, so the only light was from the car. This made it more difficult to find the cookie and added an extra layer of excitement to the game.

The car was controlled using a custom Discord.js bot, which could be accessed by sending a command in the Discord chat. The bot would then provide the user with custom buttons to control the car's movement and direction, the gripper's movements, and the light. To view the live camera feed, I used MonaServer to receive the video on my computer and then streamed it through Discord, allowing my friends to watch and control the car from the comfort of the Discord chat room. With this setup, everyone could participate in the cookie-finding game and have a thrilling time together.

## Images

![App Screenshot](https://raw.githubusercontent.com/genti91/ardu-car/main/images/car1.jpg?token=GHSAT0AAAAAABWKGXPFSL46RK7SLPHIPNAMY7JP5FQ)

![App Screenshot](https://raw.githubusercontent.com/genti91/ardu-car/main/images/car2.jpg?token=GHSAT0AAAAAABWKGXPEHFIXVON25OAP64EWY7JP5YA)

![App Screenshot](https://raw.githubusercontent.com/genti91/ardu-car/main/images/rfid.jpg?token=GHSAT0AAAAAABWKGXPESDVQJLLJCQWVL3A4Y7JP6GA)

![App Screenshot](https://raw.githubusercontent.com/genti91/ardu-car/main/images/3d-parts.png?token=GHSAT0AAAAAABWKGXPFMRKAETE2KTNNV6GEY7JP6IQ)
