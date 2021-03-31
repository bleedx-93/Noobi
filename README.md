# Noobi
A Simple tool to execute shellcode with the ability to detect mouse movement

Features:
- Sandbox evasion through detecting mouse movement and hardware resources
  - If in 10 seconds the mouse cursor didn't move it would terminate it self
  - If the CPU core are less than 2 and the RAM is less than 2048 it would terminate it self
- Using HeapAlloc instead of VirtualAlloc
- Dynamic API resolution
- String Obfuscation
- Low detection rate (on VT AV engines)

How to Use:
1. Put your shellcode in the shellcode variable
2. Compile the Code
3. Execute it by CMD or PowerShell
 
 <img src="Images/VT.png" width="1000">
