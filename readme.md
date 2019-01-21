# 3D rendering engine for the course DV1568.

Task list 
- [ ] Deferred Rendering
- [ ] Obj Parsing - Steven 
> The fileloader class contains the obj parser. Here we read the file, 
line by line. Find and collect the different useful sets of data, i.e 
vertices, uv's and even normals. We place them into their own 
std::vector. When reading the faces we lookup the specific vertices, uvs 
and normals, and place them into the std::vector for triangles. 
- [ ] Height Map - Ludwig
- [ ] Normal Mapping - Steven
- [ ] Shadow Mapping - Ludwig 
- [ ] Front and Back Rendering - Ludwig
- [ ] Back Face Culling in GS - Steven
- [ ] Billboarded Particles - Steven
- [ ] Glow Effect - Ludwig

2019-01-03
> The project is setup as a base right now, what has been implemented is 
just a simple window manager and some other smaller details. 
Currently working on implementing an .obj parser and a simple control 
manager. 


