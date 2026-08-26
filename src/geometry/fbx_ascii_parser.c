#include "geometry/fbx_ascii_parser.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "geometry/mesh.h"

bool contains_string(const char* string, const char* buffer)
{
    int stringLength = strlen(string);
    int bufferLength = strlen(buffer);
    
    if (stringLength > bufferLength)
        return false;
   
    //find the first character
    for(int i=0; i<bufferLength; i++)
    {
        if(string[0] == buffer[i])
        {
            char tempString[stringLength + 1]; //create the tempString using the loop (gotta add the nullterm)
            for(int j=0; j<stringLength; j++)
            {
                tempString[j] = buffer[i + j];
            }
            tempString[stringLength] = '\0';

            if (strncmp(tempString, string, stringLength) == 0) 
                return true;
        }
    }
   
    return false; //string not found in buffer
}


// //it seems to me like the only practical way to do this is to just read in the entire file as a string
// char *read_entire_file(const char *filename) 
// {
//     FILE *fp = fopen(filename, "rb"); //open file in binary mode for correct size in ftell
//     if (!fp)
//     {
//         perror("Failed to open file");
//         return NULL;
//     }

//     //go to the end of the file
//     if (fseek(fp, 0L, SEEK_END) != 0) 
//     {
//         perror("Error seeking to end of file");
//         fclose(fp);
//         return NULL;
//     }

//     //get the size of the file
//     long bufsize = ftell(fp);
//     if (bufsize == -1) 
//     {
//         perror("Error getting file size");
//         fclose(fp);
//         return NULL;
//     }

//     //allocate our buffer to that size (+1 for null terminator if needed for text processing)
//     char *source = malloc(sizeof(char) * (bufsize + 1));


//     //go back to start of the file
//     if (fseek(fp, 0L, SEEK_SET) != 0) {
//         perror("Error seeking to start of file");
//         free(source);
//         fclose(fp);
//         return NULL;
//     }

//     //read the entire file into memory
//     size_t newLen = fread(source, sizeof(char), bufsize, fp);
//     if (ferror(fp) != 0) {
//         perror("Error reading file");
//         free(source);
//         fclose(fp);
//         return NULL;
//     } else {
//         source[newLen] = '\\0'; //tack on the null terminator
//     }

//     fclose(fp);
//     return source;
// }

char *read_entire_file(const char *filename)
{
    FILE *fp = fopen(filename, "rb");
    if (!fp)
    {
        perror("fopen");
        return NULL;
    }

    if (fseek(fp, 0, SEEK_END) != 0)
    {
        perror("fseek");
        fclose(fp);
        return NULL;
    }

    long size = ftell(fp);
    if (size < 0)
    {
        perror("ftell");
        fclose(fp);
        return NULL;
    }

    rewind(fp);

    char *buffer = malloc((size_t)size + 1);
    if (!buffer)
    {
        perror("malloc");
        fclose(fp);
        return NULL;
    }

    size_t read = fread(buffer, 1, (size_t)size, fp);
    if (read != (size_t)size)
    {
        perror("fread");
        free(buffer);
        fclose(fp);
        return NULL;
    }

    buffer[size] = '\0'; // null terminate for ASCII FBX

    fclose(fp);
    return buffer;
}



int find_substring_index(const char *haystack, const char *needle){
    if (!*needle)
        return 0;

    for (int i = 0; haystack[i]; i++){
        int j = 0;
        while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j]){
            j++;
        }

        if (!needle[j])
            return i; //found
    }
    return -1; //not found
}

int get_int_count(const char *buffer){
    char *v = strstr(buffer, "PolygonVertexIndex:"); //find the amount of ints 

    char *star = strchr(v, '*'); //find the *
    
    if (star){
        int count = atoi(star + 1);
        return count; 
    }
    return -1;
}


int get_float_count(const char *buffer){
    char *v = strstr(buffer, "Vertices:"); //find the amount vertices
    
    char *star = strchr(v, '*'); //find the *
    
    if (star){
        int count = atoi(star + 1);
        return count; 
    }
    return -1;
}


struct Edges* get_edges()
{
    const char *theEntireFuckingFbxFileAsAString =
        read_entire_file("assets/3dpea.com_attempt1.fbx");

    int edges_start_index = find_substring_index(theEntireFuckingFbxFileAsAString, "PolygonVertexIndex:");

    int int_count = get_int_count(theEntireFuckingFbxFileAsAString);

    struct Edges *edges = malloc(sizeof(struct Edges)); //the struct is allocated on the heap
    edges->indices = malloc(sizeof(int) * int_count);   //the struct contains a pointer to the heap (indices), the pointer needs that memory to be allocated on the heap
    edges->length = 0;                                  //lengh is a field within the struct so it is already on the heap beause the struct is on the heap
                                                        //so the pointer itself is also on the heap but the memory it points to will not be on the heap unless you explictly malloc it on the heap
    int iterator = edges_start_index;

    while (theEntireFuckingFbxFileAsAString[iterator] != 'a')
        iterator++;

    while (theEntireFuckingFbxFileAsAString[iterator] != ':')
        iterator++;

    iterator++; //step into the whitespace after ':'

    while (theEntireFuckingFbxFileAsAString[iterator] == ' ')
        iterator++;

    char *p = (char *)theEntireFuckingFbxFileAsAString + iterator;

    while (*p)
    {
        //skip the trash
        while (*p == ',' || *p == ' ' || *p == '\n' || *p == '\t')
            p++;

        int current_int = 0;
        sscanf(p, "%d", &current_int);

        edges->indices[edges->length++] = current_int;

        //move foward to the next number
        while (*p != ',' && *p != ' ' && *p != '\n' && *p != '\t' && *p != '}')
            p++;

        if (*p == '}')
            break;
    }

    int neg = 0; //TODO REMOEV THIS 
for (int i = 0; i < edges->length; i++)
    neg += (edges->indices[i] < 0);

    return edges;
}


struct Vertices* get_vertices()
{
    const char *theEntireFuckingFbxFileAsAString = read_entire_file("assets/3dpea.com_attempt1.fbx");

    int vertices_start_index = find_substring_index(theEntireFuckingFbxFileAsAString, "Vertices:"); //find vertices

    //init the float array
    int float_count = get_float_count(theEntireFuckingFbxFileAsAString);
    float *float_array = malloc(sizeof(float) * (float_count - 1)); //heap allocation

    //find the a
    int iterator = vertices_start_index;
    while(theEntireFuckingFbxFileAsAString[iterator] != 'a'){
        iterator++;
    }
    //find the ':' after the 'a'
    while(theEntireFuckingFbxFileAsAString[iterator] != ':'){
        iterator++;
    }
    //go one past it to enter the whitespace 
    iterator++;

    //traverse past all the whitespace to the first character which should be an ascii number
    while(theEntireFuckingFbxFileAsAString[iterator] == ' '){
        iterator++;
    }


    char *p = theEntireFuckingFbxFileAsAString + iterator;

    int floats_parsed = 0;

    while(*p) 
    {
        while(*p == ',' || *p == ' ' || *p == '\n' || *p == '\t') //if p is standing on trash walk forward
            p++;
        
        float current_float = -1;
        sscanf(p, "%f", &current_float);
        float_array[floats_parsed] = current_float;
        floats_parsed++;
        
        
        //skip all the trash (go to the next comma)
        while(*p != ',' && *p != ' ' && *p != '\n' && *p != '\t')
            p++;
        
        if(*p == '}' || *p == ' ')
            break;
    }

    float a = float_array[1084];
    float b = float_array[1085];

    //create the vec3 array
    struct Vertices *vertices = malloc(sizeof(struct Vertices));
    vertices->length = (float_count / 3);
    vertices->vec3array = malloc(sizeof(struct vec3) * vertices->length);


    for(int i=0; i < float_count; i+=3) {
        vertices->vec3array[i/3].x = float_array[i];
        vertices->vec3array[i/3].y = float_array[i+1];
        vertices->vec3array[i/3].z = float_array[i+2];
    }

    return vertices; //i want vertices entirely heap allocated
}



struct Mesh* get_mesh()
{
    // Allocate the Mesh itself on the heap
    struct Mesh *mesh = malloc(sizeof(struct Mesh));
    if (!mesh) return NULL;

    // Use your fully heap-allocated functions
    mesh->vertices = get_vertices(); // returns struct Vertices* 
    mesh->edges = get_edges();    // returns struct Edges*

    return mesh;
}








