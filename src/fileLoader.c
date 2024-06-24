#include "jsonParser.h"
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entity.c"


//TODO: Move to jsonParser maybe, feels out of place with my garbage?
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


//TODO: Cleanup File, hard to be sure it even works
void loadEntitiesFromJson(multitypearray  entitiesJson){
    
    for(int i = 0; i < entitiesJson.objectCount; i++){

        int entityId = newEntity(entitiesJson.objectList[i].keyList[0].value);
        multitypearray components = entitiesJson.objectList[i].subArrayList[0];
        int transformId = -1;

        //TODO: Refactor a bit or hide away
        //TODO: Reorder if needed
        for(int j = 0; j < components.objectCount; j++){

            json_object component = components.objectList[j];
            if(strcmp(component.keyList[0].value, "transform")) {
                Vector3 position = (Vector3){
                    atof(component.subObjects[0].keyList[0].value),
                    atof(component.subObjects[0].keyList[1].value),
                    atof(component.subObjects[0].keyList[2].value)};
                Vector3 rotation = (Vector3){
                    atof(component.subObjects[1].keyList[0].value),
                    atof(component.subObjects[1].keyList[1].value),
                    atof(component.subObjects[1].keyList[2].value)};
                Vector3 scale = (Vector3){
                    atof(component.subObjects[2].keyList[0].value),
                    atof(component.subObjects[2].keyList[1].value),
                    atof(component.subObjects[2].keyList[2].value)};

                //TODO: store result somehow?
                newTransform(entityId, position, rotation, scale);
            }
            else if(strcmp(component.keyList[0].value, "primativeRenderer")) {
                newPrimativeRenderer
                    (
                        entityId,
                        transformId,
                        component.subObjects[0].keyList[0].value, //shapeStr
                        component.subObjects[0].keyList[1].value // isActive
                    );
            }
            else if(strcmp(component.keyList[0].value, "playerInput")) {
                 
            }
        }
    } 
// Lunix Raid Times
//monday tuesday -> 1:30pm
//another day -> 7:30pm

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





