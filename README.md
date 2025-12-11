# 🐍 GenerateMakefile 🏗️

### **Tired of writing Makefiles? Let the computer do it\!**

\<p align="center"\>
\<img src="[https://img.shields.io/badge/Language-Python%203-blue?style=for-the-badge\&logo=python](https://www.google.com/search?q=https://img.shields.io/badge/Language-Python%25203-blue%3Fstyle%3Dfor-the-badge%26logo%3Dpython)" alt="Python 3 Badge"\>
\<img src="[https://img.shields.io/badge/Build%20Tool-Makefile-success?style=for-the-badge\&logo=gnu](https://www.google.com/search?q=https://img.shields.io/badge/Build%2520Tool-Makefile-success%3Fstyle%3Dfor-the-badge%26logo%3Dgnu)" alt="Makefile Badge"\>
\<img src="[https://img.shields.io/badge/Automation-100%25-red?style=for-the-badge](https://www.google.com/search?q=https://img.shields.io/badge/Automation-100%2525-red%3Fstyle%3Dfor-the-badge)" alt="100% Automation Badge"\>
\</p\>

## ✨ What is GenerateMakefile?

**GenerateMakefile** is a lightweight, command-line Python utility that **automatically generates a simple, executable `Makefile`** for your C projects. Forget boilerplate\! Just tell it the desired executable name and the source files, and you're ready to compile. 🤯

If you're dealing with small to medium-sized projects and just need a quick, reliable `all` target, this script is your **best friend**. 🫂

## 🚀 Key Features — Why You Need This

  * **⚡️ Instant Makefile Generation:** Creates a valid `Makefile` with a single line command. No manual editing required.
  * **🎯 Smart Argument Filtering:** It intelligently separates your source files from flags (like `-make`), ensuring a clean build recipe every time.
  * **🔥 Automatic Compilation (Optional):** Use the magic flag to generate the file **AND** run `make` immediately\! **One command to rule them all.**
  * **✅ Cross-Platform:** It's Python\! It works wherever you code.

## 🛠️ How to Use It (It's ridiculously simple)

### 1\. Save the script

Save the Python code above as `mkmake.py`.

### 2\. Run it\!

The script expects the **target executable name** first, followed by the **list of your source files (without the .c extension)**.

#### Basic Usage

Generate the `Makefile` and stop.

```bash
$ python3 mkmake.py <EXEC_NAME> <FILE1> <FILE2> ...
```

  * **Example:**

<!-- end list -->

```bash
$ python3 mkmake.py my_program main helper utils
```

This will create a `Makefile` containing:

```makefile
my_program: main.c helper.c utils.c
	cc main.c helper.c utils.c -o my_program
```

#### The Power-User Option: Generate and Make\!

Generate the `Makefile` **AND** immediately run the `make` command to compile your project. **Instant gratification\!** 🥳

```bash
$ python3 mkmake.py <EXEC_NAME> <FILE1> <FILE2> ... -make
```

  * **Example:**

<!-- end list -->

```bash
$ python3 mkmake.py my_app server client -make
```

*(The `-make` flag is ignored when creating the file list but triggers the execution.)*

## 🧑‍💻 The Source Code (Under the Hood)

Here is the clean, efficient code that powers your automation:

```python
import sys
import subprocess as sp

def main():
    av = sys.argv
    ac = len(av)
    if ac < 3:
        print("Missing args: Usage: python3 mkmake.py <EXEC_NAME> <FILE1> <FILE2> ... [-make]")
        return
    
    # Filter files from flags like -make
    file_names = [s for s in av[2:] if s[0] != '-']
    
    compiled_name = av[1]
    
    # Construct the required file list (target dependency line)
    req_files = ".c ".join(file_names) + ".c"
    
    # Construct the compilation command (recipe line)
    comp_line = "\tcc " + ".c ".join(file_names) + ".c -o " + compiled_name
    
    # Assemble the Makefile content
    line1 = compiled_name + ": " + req_files
    line2 = comp_line
    final = line1 + "\n" + line2

    # Write the file
    open("Makefile", "w").write(final)
    print("Makefile written successfully!")
    print("---")
    print(final)
    print("---")

    # The magic feature: Compile immediately!
    if "-make" in av:
        print("Running 'make' now...")
        sp.run("make", shell=True)

if __name__ == "__main__":
    main()
```

## 🙏 Contribution

Got ideas for more default targets (like `clean`)? Find a bug? Pull requests are welcome\! Let's make this tool even better\! 💖
