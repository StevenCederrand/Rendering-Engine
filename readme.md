# 3D rendering engine for the course DV1568.

Task list 
- [ ] Deferred Rendering
- [x] Obj Parsing - Steven 
> I have reworked the parser and now it works well. What 
happens is the following. Initially the Fileloader inserts 
all valid extensions to its extension vector. So everyfile 
that we request to look up, we will check to see if we 
support it. If it's an .obj then we start to read the 
contents of the file. All positions, normals and uv's are 
pushed into their own vector. When interpretting faces we 
pass through a Mesh type. Which contains a vector of 
"Vertex"(a combination of positions, normals and UV's). 
Each face is divided upp in the following structure, 
V/VT/VN. We add all of this data to the mesh. Then all we 
have left is the .mtl file. Which is fairly straight 
forward. We save all relevant data such as colours into 
glm::vec3 etc. 
- [ ] Height Map - Ludwig
- [ ] Normal Mapping - Steven
- [ ] Shadow Mapping - Ludwig 
- [ ] Front and Back Rendering - Ludwig
- [ ] Back Face Culling in GS - Steven //Allt som vi behöver göra är att 
inte emitta de faces som är vänd från kameran. Dvs. att vi använder ej 
emitvertex och emit primitive. 
- [ ] Billboarded Particles - Steven
- [ ] Glow Effect - Ludwig


2019-02-05
To do list for week 6. 
- [ ] Implement some form of indexing
- [ ] Complete normal mapping -- Working on tangent space
- [ ] Height Mapping?
- [ ] 



2019-01-03
> The project is setup as a base right now, what has been implemented is 
just a simple window manager and some other smaller details. 
Currently working on implementing an .obj parser and a simple control 
manager. 


