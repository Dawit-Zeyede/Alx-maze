# MAZE

## 🎮 Introduction

**MAZE** is a captivating 3D game developed using SDL2 and raycasting techniques. The game creates an immersive 3D maze environment where players navigate through complex labyrinths, interact with walls, and experience fundamental 3D rendering. Leveraging raycasting, MAZE renders walls with a sense of depth and perspective, while player controls and interactive elements like weapons and enemies add layers of engagement.

This project serves as a practical demonstration of 3D game development principles, offering a hands-on experience with the fundamentals of game rendering, player mechanics, and collision detection. MAZE is not just a game; it's a testament to the power of SDL2 and the elegance of raycasting in game development.

**Deployed Site:** [Watch the demo on YouTube](https://youtu.be/tOl8FLGQvOE)  
**Final Project Blog Article:** [LinkedIn Article](https://www.linkedin.com/posts/dawit-zeyede10_linkthe-maze-activity-7242053902056013826-Cwqc?utm_source=share&utm_medium=member_desktop)  
**Author LinkedIn:** [Dawit Zeyede](https://www.linkedin.com/in/dawit-zeyede10/)

## 🚀 Installation

Setting up MAZE on your local machine involves a few straightforward steps. Follow the instructions below to get started:

1. **Clone the Repository:**
    First, clone the repository from GitHub to your local machine. This will create a local copy of the project that you can build and run.
    ```bash
    git clone https://github.com/Dawit-Zeyede/Alx-maze.git
    cd Alx-maze
    ```

2. **Install Dependencies:**
    MAZE depends on SDL2 and SDL2_image libraries for rendering and image handling. On Debian-based systems like Ubuntu, you can install these libraries using the following command:
    ```bash
    sudo apt-get install libsdl2-dev libsdl2-image-dev
    ```

3. **Build the Project:**
    Once the dependencies are installed, compile the project using `gcc`. This command will compile the source files and link them with the SDL2 and SDL2_image libraries.
    ```bash
    gcc -Wall -Werror -Wextra -pedantic -o maze src/*.c -lSDL2 -lSDL2_image -lm
    ```
    The `-lm` flag is crucial here as it links the math library required for functions like `cos` and `sin`.

4. **Run the Application:**
    After building the project, you can run the compiled binary. The game window will open, and you can start exploring the maze.
    ```bash
    ./maze
    ```

## 🎮 Usage

MAZE provides a basic yet engaging gameplay experience. Use the following controls to navigate and interact with the game:

- `W` - Move forward through the maze.
- `S` - Move backward.
- `A` - Turn left to change your orientation.
- `D` - Turn right to adjust your view.
- Arrow Keys - Rotate the view to look around.
- `M` - Toggle the visibility of the 2D map to help with navigation.

These controls are designed to be intuitive and easy to use, allowing players to focus on exploring the maze and enjoying the 3D environment.

## 🤝 Contributing

Contributions to the MAZE project are encouraged! Whether you’re interested in adding new features, improving existing functionality, or fixing bugs, your input is valuable. To contribute:

1. **Fork the Repository:** Create your own copy of the repository on GitHub.
2. **Create a Feature Branch:** Switch to a new branch for your changes.
    ```bash
    git checkout -b feature-branch
    ```
3. **Commit Your Changes:** Record your changes with a meaningful commit message.
    ```bash
    git commit -am 'Add new feature'
    ```
4. **Push to the Branch:** Upload your changes to your fork on GitHub.
    ```bash
    git push origin feature-branch
    ```
5. **Create a Pull Request:** Open a pull request on the main repository to propose your changes.

Please ensure that your contributions align with the project's coding style and include tests for new features where applicable.

## 🔗 Related Projects

Here are some related projects that complement or extend the MAZE project:

- [Alx-maze_landing](https://github.com/Dawit-Zeyede/Alx-maze_landing) - An additional project exploring more advanced features and enhancements related to the MAZE game.

## 📜 Licensing

At this time, no license has been specified for the MAZE project. Feel free to use, modify, and distribute the code according to your needs, but be mindful of the project's licensing status.

## 🖼️ Screenshots

Here's a glimpse of MAZE in action:

![Maze Screenshot](images/screenshot.png)

## 🛠️ Technical Challenges and Future Vision

**Technical Challenges:**

- **Raycasting Implementation:** Developing the raycasting logic required a deep understanding of trigonometry and SDL2’s rendering capabilities. Ensuring accurate distance calculations and rendering walls with proper perspective was challenging but essential for creating a realistic 3D effect.
- **Player Movement and Collision Detection:** Fine-tuning player movement and collision detection with walls involved overcoming initial issues with sliding and accurate interaction. It required iterative testing and adjustments to achieve smooth gameplay.

**Future Vision:**

- **Enhanced Graphics and Effects:** Future iterations of MAZE could benefit from advanced visual effects such as dynamic lighting, improved textures, and environmental effects to create a more immersive experience.
- **Expanded Maze Features:** Introducing more complex maze designs, interactive elements, and diverse enemy types would enhance gameplay and offer players new challenges.
- **Optimized Performance:** Further optimization of the raycasting algorithm and rendering pipeline could improve performance, reduce lag, and provide a smoother gaming experience.

**Personal Journey:**

Creating MAZE was both a technical and creative challenge. It involved grappling with complex algorithms, fine-tuning game mechanics, and learning new tools and techniques. Despite the struggles, the project has been a rewarding experience, showcasing my growth in game development and my passion for creating engaging experiences. I’m excited about the possibilities for future improvements and am grateful for the opportunity to share this project with others.

Feel free to explore the code, try out the game, and contribute to its development. Thank you for your interest in MAZE!
