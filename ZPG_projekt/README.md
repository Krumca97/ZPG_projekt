# ZPG_projekt

---

Projekt do předmětu ZPG(Základy počítačové grafiky).

Vytvořil: Aleš Laník, LAN0229.

---

## Linkování knihoven

Tento návod ukazuje **kde stáhnout** knihovny **GLFW**, **GLEW** a **GLM** z internetu a **jak je nalinkovat** ve **Visual Studiu**.  
Poznámka: **`glew32.dll` musí být umístěná u .exe**.

---

## Knihovny

- **GLFW**:  
  https://www.glfw.org/  → **Download** nebo (GitHub releases: https://github.com/glfw/glfw/releases)

- **GLEW**:  
  http://glew.sourceforge.net/  → **Windows Binaries** (ZIP)

- **GLM**:  
  https://github.com/g-truc/glm → **Releases** (ZIP)

> **x64** varianty jelikož knihovny musí být kompatibilní s 64bit buildem a ve VS budeme kompilovat pro **x64**.

---
## Doporučená struktura projektu

```
ZPG_projekt/
├─ libraries/
│  ├─ glfw/       
│  ├─ glew/       
│  └─ glm/        
├─ Projekt/       
│  ├─ .cpp a .h 
└─ README.md
```
Do `libraries/` **Extrahuj** stažené ZIPy.  
Cesty dál nastavíme **relativně** vůči `$(ProjectDir)`.

---
## Nastavení ve Visual Studiu

**Project → Properties**. Následující položky nastav pro **Debug** i **Release** a **x64** platformu.

### 1) C/C++ → General → **Additional Include Directories**

Přidej (každé na nový řádek):

```
$(ProjectDir)libraries\glfw\include
$(ProjectDir)libraries\glew\include
$(ProjectDir)libraries\glm
```
> GLM je header-only, stačí **jen include cesta**.

### 2) Linker → General → **Additional Library Directories**

```
$(ProjectDir)libraries\glfw\lib-vc2022
$(ProjectDir)libraries\glew\lib\Release\x64
```

### 3) Linker → Input → **Additional Dependencies**

```
opengl32.lib
glfw3.lib            
glew32.lib           
```
### 4) Zkopíruj **GLEW DLL** k .exe

Pokud **`glew32.lib`** , musí být **`glew32.dll`** ve **stejné složce jako .exe**:

- Zkopíruj z `libraries\glew\bin\Release\x64\glew32.dll` do `$(OutDir)` (např. `x64\Debug\`).

## Posloupnost knihoven

```cpp
#include <GL/glew.h>
#include <GLFW/glfw3.h>
...
```




