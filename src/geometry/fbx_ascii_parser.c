
#include "geometry/fbx_ascii_parser.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "geometry/mesh.h"
#include "globals.h"

bool contains_string(const char* string, const char* buffer)
{
    int stringLength = strlen(string);
    int bufferLength = strlen(buffer);

    if (stringLength > bufferLength)
        return false;

    //find the first character
    for (int i = 0; i < bufferLength; i++)
    {
        if (string[0] == buffer[i])
        {
            char tempString[stringLength + 1]; //create the tempString using the loop (gotta add the nullterm)
            for (int j = 0; j < stringLength; j++)
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

int find_substring_index(const char *haystack, const char *needle)
{
    if (!*needle)
        return 0;

    for (int i = 0; haystack[i]; i++)
    {
        int j = 0;
        while (haystack[i + j] && needle[j] && haystack[i + j] == needle[j])
        {
            j++;
        }

        if (!needle[j])
            return i; //found
    }

    return -1; //not found
}

int get_int_count(const char *buffer)
{
    char *v = strstr(buffer, "PolygonVertexIndex:"); //find the amount of ints

    char *star = strchr(v, '*'); //find the *

    if (star)
    {
        int count = atoi(star + 1);
        return count;
    }

    return -1;
}

int get_float_count(const char *buffer)
{
    char *v = strstr(buffer, "Vertices:"); //find the amount vertices

    char *star = strchr(v, '*'); //find the *

    if (star)
    {
        int count = atoi(star + 1);
        return count;
    }

    return -1;
}

struct Edges* get_edges(const char* filepath_to_fbx_ascii_model)
{
    const char *theEntireFbxFileAsAString = read_entire_file(filepath_to_fbx_ascii_model);

    int edges_start_index = find_substring_index(theEntireFbxFileAsAString, "PolygonVertexIndex:");

    int int_count = get_int_count(theEntireFbxFileAsAString);

    struct Edges *edges = malloc(sizeof(struct Edges));
    edges->indices = malloc(sizeof(int) * int_count);
    edges->length = 0;

    int iterator = edges_start_index;

    while (theEntireFbxFileAsAString[iterator] != 'a')
        iterator++;

    while (theEntireFbxFileAsAString[iterator] != ':')
        iterator++;

    iterator++; //step into the whitespace after ':'

    while (theEntireFbxFileAsAString[iterator] == ' ')
        iterator++;

    const char *p = theEntireFbxFileAsAString + iterator;

    while (*p)
    {
        //skip the trash (including Windows carriage returns)
        while (*p == ',' || *p == ' ' || *p == '\n' ||
               *p == '\r' || *p == '\t')
            p++;

        if (*p == '}' || *p == '\0' || edges->length >= int_count)
            break;

        int current_int = 0;
        sscanf(p, "%d", &current_int);

        edges->indices[edges->length++] = current_int;

        //move forward to the next number
        while (*p != ',' && *p != ' ' && *p != '\n' &&
               *p != '\r' && *p != '\t' && *p != '}' && *p != '\0')
            p++;

        if (*p == '}')
            break;
    }

    int neg = 0; //TODO REMOVE THIS
    for (int i = 0; i < edges->length; i++)
        neg += (edges->indices[i] < 0);

    free((void *)theEntireFbxFileAsAString);
    return edges;
}

struct Vertices* get_vertices(const char* filepath_to_fbx_ascii_model)
{
    const char *theEntireFbxFileAsAString = read_entire_file(filepath_to_fbx_ascii_model);

    int vertices_start_index = find_substring_index(theEntireFbxFileAsAString, "Vertices:"); //find vertices

    //init the float array
    int float_count = get_float_count(theEntireFbxFileAsAString);
    float *float_array = malloc(sizeof(float) * float_count); //heap allocation

    //find the a
    int iterator = vertices_start_index;
    while (theEntireFbxFileAsAString[iterator] != 'a')
    {
        iterator++;
    }

    //find the ':' after the 'a'
    while (theEntireFbxFileAsAString[iterator] != ':')
    {
        iterator++;
    }

    //go one past it to enter the whitespace
    iterator++;

    //traverse past all the whitespace
    while (theEntireFbxFileAsAString[iterator] == ' ')
    {
        iterator++;
    }

    const char *p = theEntireFbxFileAsAString + iterator;

    int floats_parsed = 0;

    while (*p)
    {
        //skip separators and whitespace, including Windows carriage returns
        while (*p == ',' || *p == ' ' || *p == '\n' ||
               *p == '\r' || *p == '\t')
            p++;

        if (*p == '}' || *p == '\0' || floats_parsed >= float_count)
            break;

        float current_float = -1;
        sscanf(p, "%f", &current_float);

        float_array[floats_parsed] = current_float;
        floats_parsed++;

        //move forward to the next number
        while (*p != ',' && *p != ' ' && *p != '\n' &&
               *p != '\r' && *p != '\t' && *p != '}' && *p != '\0')
            p++;

        if (*p == '}')
            break;
    }

    //debug float parsing
    FILE *debug = fopen("mesh_debug.txt", "a");

    if (debug)
    {
        fprintf(debug, "FILE: %s\n", filepath_to_fbx_ascii_model);
        fprintf(debug, "FLOATS PARSED: %d / %d\n", floats_parsed, float_count);
        fclose(debug);
    }

    float a = float_array[float_count - 2];
    float b = float_array[float_count - 1];

    //float a = float_array[1084]; //DS4
    //float b = float_array[1085]; //DS4
    //float a = float_array[7834]; //XBOX ONE
    //float b = float_array[7835]; //XBOX ONE

    //create the vec3 array
    struct Vertices *vertices = malloc(sizeof(struct Vertices));
    vertices->length = (float_count / 3);
    vertices->vec3array = malloc(sizeof(struct vec3) * vertices->length);

    for (int i = 0; i < float_count; i += 3)
    {
        vertices->vec3array[i / 3].x = float_array[i];
        vertices->vec3array[i / 3].y = float_array[i + 1];
        vertices->vec3array[i / 3].z = float_array[i + 2];
    }

    free(float_array);
    free((void *)theEntireFbxFileAsAString);

    return vertices; //i want vertices entirely heap allocated
}

struct Mesh* get_mesh(const char* filepath_to_fbx_ascii_model)
{
    // Allocate the Mesh itself on the heap
    struct Mesh *mesh = malloc(sizeof(struct Mesh));
    if (!mesh)
        return NULL;

    // Use your fully heap-allocated functions
    mesh->vertices = get_vertices(filepath_to_fbx_ascii_model);
    mesh->edges = get_edges(filepath_to_fbx_ascii_model);

    printf("MESH LOADED: vertices=%d, edges=%d\n",
           mesh->vertices->length,
           mesh->edges->length);

    if (mesh->edges->length > 0)
    {
        printf("FIRST EDGE INDEX: %d\n", mesh->edges->indices[0]);
    }

    FILE *f = fopen("mesh_debug.txt", "a");

    if (f)
    {
        fprintf(f, "Vertices: %d\n", mesh->vertices->length);
        fprintf(f, "Edges: %d\n", mesh->edges->length);

        for (int i = 0; i < 5 && i < mesh->vertices->length; i++)
        {
            struct vec3 v = mesh->vertices->vec3array[i];
            fprintf(f, "Vertex %d: %f %f %f\n", i, v.x, v.y, v.z);
        }

        for (int i = 0; i < 10 && i < mesh->edges->length; i++)
            fprintf(f, "Edge %d: %d\n", i, mesh->edges->indices[i]);

        fclose(f);
    }

    return mesh;
}
