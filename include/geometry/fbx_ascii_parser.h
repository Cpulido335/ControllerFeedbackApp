#ifndef FBX_ASCII_PARSER_H // make sure underscores are allowed in c file names
#define FBX_ASCII_PARSER_H

#include "math/vec.h" //TODO i dont think we need this if we just do include mesh
#include "geometry/mesh.h"

#include <stdbool.h> 
//Read in the FBXascii file since its just a textfile
//locate the String 'Vertices', the length of vec3 *arrayOfVertices will be *1086 / 3. malloc that bitch
//then locate the string 'a: ' from this point up until the next whitespace we need to shove that entire chunk of text thing into a string
//we can count the amount of characters in the first pass, then malloc char theEntireVerticeString[charCount + null terminator]
//on the second pass we can load every character into that bitch


bool contains_string(const char* string, const char* buffer);

struct Edges* get_edges(); //TODO question does this return an entire struct on the stack or a pointer to a struct on the heap or struct on the stack that contains a pointer to an array of vec3s on the heap how tf does this even wor
struct Vertices* get_vertices();
struct Mesh* get_mesh();




#endif 