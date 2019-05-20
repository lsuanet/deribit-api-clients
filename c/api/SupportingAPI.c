#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "SupportingAPI.h"


#define MAX_BUFFER_LENGTH 4096
#define intToStr(dst, src) \
    do {\
    char dst[256];\
    snprintf(dst, 256, "%ld", (long int)(src));\
}while(0)

// Retrieves the current time (in milliseconds). This API endpoint can be used to check the clock skew between your software and Deribit's systems.
//
object_t*
SupportingAPI_publicGetTimeGet(apiClient_t *apiClient)
{
    list_t    *localVarQueryParameters = NULL;
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/public/get_time")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/public/get_time");



    list_addElement(localVarHeaderType,"application/json"); //produces
    apiClient_invoke(apiClient,
                    localVarPath,
                    localVarQueryParameters,
                    localVarHeaderParameters,
                    localVarFormParameters,
                    localVarHeaderType,
                    localVarContentType,
                    localVarBodyParameters,
                    "GET");

    if (apiClient->response_code == 200) {
        printf("%s\n","");
    }
    //nonprimitive not container
    cJSON *SupportingAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    object_t *elementToReturn = object_parseFromJSON(SupportingAPIlocalVarJSON);
    cJSON_Delete(SupportingAPIlocalVarJSON);
    if(elementToReturn == NULL) {
        // return 0;
    }

    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
    }
    
    
    
    list_free(localVarHeaderType);
    
    free(localVarPath);
    return elementToReturn;
end:
    return NULL;

}

// Method used to introduce the client software connected to Deribit platform over websocket. Provided data may have an impact on the maintained connection and will be collected for internal statistical purposes. In response, Deribit will also introduce itself.
//
object_t*
SupportingAPI_publicHelloGet(apiClient_t *apiClient ,char * client_name ,char * client_version)
{
    list_t    *localVarQueryParameters = list_create();
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/public/hello")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/public/hello");




    // query parameters
    char *keyQuery_client_name;
    char * valueQuery_client_name;
    keyValuePair_t *keyPairQuery_client_name = 0;
    if (client_name)
    {
        keyQuery_client_name = strdup("client_name");
        valueQuery_client_name = strdup((client_name));
        keyPairQuery_client_name = keyValuePair_create(keyQuery_client_name, valueQuery_client_name);
        list_addElement(localVarQueryParameters,keyPairQuery_client_name);
    }

    // query parameters
    char *keyQuery_client_version;
    char * valueQuery_client_version;
    keyValuePair_t *keyPairQuery_client_version = 0;
    if (client_version)
    {
        keyQuery_client_version = strdup("client_version");
        valueQuery_client_version = strdup((client_version));
        keyPairQuery_client_version = keyValuePair_create(keyQuery_client_version, valueQuery_client_version);
        list_addElement(localVarQueryParameters,keyPairQuery_client_version);
    }
    list_addElement(localVarHeaderType,"application/json"); //produces
    apiClient_invoke(apiClient,
                    localVarPath,
                    localVarQueryParameters,
                    localVarHeaderParameters,
                    localVarFormParameters,
                    localVarHeaderType,
                    localVarContentType,
                    localVarBodyParameters,
                    "GET");

    if (apiClient->response_code == 200) {
        printf("%s\n","");
    }
    //nonprimitive not container
    cJSON *SupportingAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    object_t *elementToReturn = object_parseFromJSON(SupportingAPIlocalVarJSON);
    cJSON_Delete(SupportingAPIlocalVarJSON);
    if(elementToReturn == NULL) {
        // return 0;
    }

    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
    }
    list_free(localVarQueryParameters);
    
    
    list_free(localVarHeaderType);
    
    free(localVarPath);
    free(keyQuery_client_name);
    free(valueQuery_client_name);
    keyValuePair_free(keyPairQuery_client_name);
    free(keyQuery_client_version);
    free(valueQuery_client_version);
    keyValuePair_free(keyPairQuery_client_version);
    return elementToReturn;
end:
    return NULL;

}

// Tests the connection to the API server, and returns its version. You can use this to make sure the API is reachable, and matches the expected version.
//
object_t*
SupportingAPI_publicTestGet(apiClient_t *apiClient ,expected_result_e expected_result)
{
    list_t    *localVarQueryParameters = list_create();
    list_t    *localVarHeaderParameters = NULL;
    list_t    *localVarFormParameters = NULL;
    list_t *localVarHeaderType = list_create();
    list_t *localVarContentType = NULL;
    char      *localVarBodyParameters = NULL;

    // create the path
    long sizeOfPath = strlen("/public/test")+1;
    char *localVarPath = malloc(sizeOfPath);
    snprintf(localVarPath, sizeOfPath, "/public/test");




    // query parameters
    char *keyQuery_expected_result;
    expected_result_e valueQuery_expected_result;
    keyValuePair_t *keyPairQuery_expected_result = 0;
    if (expected_result)
    {
        keyQuery_expected_result = strdup("expected_result");
        valueQuery_expected_result = (expected_result);
        keyPairQuery_expected_result = keyValuePair_create(keyQuery_expected_result, (void *)valueQuery_expected_result);
        list_addElement(localVarQueryParameters,keyPairQuery_expected_result);
    }
    list_addElement(localVarHeaderType,"application/json"); //produces
    apiClient_invoke(apiClient,
                    localVarPath,
                    localVarQueryParameters,
                    localVarHeaderParameters,
                    localVarFormParameters,
                    localVarHeaderType,
                    localVarContentType,
                    localVarBodyParameters,
                    "GET");

    if (apiClient->response_code == 200) {
        printf("%s\n","");
    }
    //nonprimitive not container
    cJSON *SupportingAPIlocalVarJSON = cJSON_Parse(apiClient->dataReceived);
    object_t *elementToReturn = object_parseFromJSON(SupportingAPIlocalVarJSON);
    cJSON_Delete(SupportingAPIlocalVarJSON);
    if(elementToReturn == NULL) {
        // return 0;
    }

    //return type
    if (apiClient->dataReceived) {
        free(apiClient->dataReceived);
    }
    list_free(localVarQueryParameters);
    
    
    list_free(localVarHeaderType);
    
    free(localVarPath);
    free(keyQuery_expected_result);
    free(valueQuery_expected_result);
    keyValuePair_free(keyPairQuery_expected_result);
    return elementToReturn;
end:
    return NULL;

}

