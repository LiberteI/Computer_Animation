# Shape Morphing

A simple **OpenGL** program that morphs custom shapes (e.g., letters → stars) using **double buffering** and a **modular C++ architecture**.

🎥 **Demo:** [YouTube – Shape Morphing](https://www.youtube.com/watch?v=7SlBEJYV8-g)

---

## 🚀 Features

- Morphs between custom shapes (letters → stars)
- Smooth animation using **double buffering**
- **Event-driven** user interaction (mouse input)
- **Manual shape resampling** and **LERP (linear interpolation)**
- Modularized **C++ header/source architecture**

---

## 🧩 Code Architecture

main.cpp → Handles user input & display
│
├── Character → Defines custom letter shapes
├── Shape → Loads vertices for each shape
├── Point → Helper class for vertex representation
├── Draw → Connects vertices and draws the shape
└── Morph → Handles resampling, interpolation, and transformation


---

## ⚙️ Technical Highlights

- **Language:** C++
- **Graphics Library:** OpenGL + GLUT  
- **Concepts Used:**
  - Modular design (headers + sources)
  - Double buffering for frame rendering
  - Event-driven graphics manipulation
  - Linear interpolation (LERP)
  - Manual vertex resampling

---

## 💡 Lessons Learned

1. **Understand library limitations**  
   Discovered that `glPolygon` only supports convex shapes — causing rendering errors for concave shapes like stars.

2. **Plan ahead**  
   Designing architecture and writing self-documenting code early saved significant refactoring time later.

---

## 🔁 Refactoring Impact

Originally, the project consisted of **700+ lines** in a single `main.cpp` file.  
After modularization into **5 header/source pairs**, the main file shrank to **~100 lines**, achieving:
- Clearer separation of responsibilities  
- Easier debugging and maintenance  
- Better scalability for future features  

---

## 🧠 Concepts Demonstrated

- OpenGL rendering pipeline  
- Vertex-based morphing  
- Event-driven input handling  
- Object-oriented C++ design  
- Double-buffered rendering loop  

---

## 🧱 Run
Click on **app**


🧑‍💻 Author

Yiming Yang (Liberté)
BSc Computer Science, Music Minor @ Dalhousie University
🎮 Indie Game Developer & Software Engineer
🎹 Pianist | Halifax, NS, Canada
