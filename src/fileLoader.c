#include "jsonParser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core.h"



char* readEntireFile(char* fileName){
// https://stackoverflow.com/questions/9069205/how-do-i-free-memory-in-c
    FILE *f = fopen(fileName, "rb");
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);

    string[fsize] = 0;
    return string;
}

void loadEntitiesFromJson(multitypearray  entitiesJson){
    
    for(int i = 0; i < entitiesJson.objectCount; i++){
        if(strcmp(entitiesJson.objectList[i].keyList[0].value, "transform")) {
             
        }
        else if(strcmp(entitiesJson.objectList[i].keyList[0].value, "primativeRenderer")) {
             
        }
        else if(strcmp(entitiesJson.objectList[i].keyList[0].value, "playerInput")) {
             
        }

    }


}

//TODO: string tables
void loadFromJsonFile(char* fileName){
    char* contents = readEntireFile(fileName);
    json_object* gameStateJson = parseJson(contents);

    loadEntitiesFromJson(gameStateJson->subArrayList[0]);

    free(contents);
    //TODO: I foreshadow a memory leak, but thats not a problem for my birthday
    free(gameStateJson);
}





