#include <stdio.h>
#include <curl/curl.h>

int main(void) {
    CURL *curl;
    CURLcode res;
    char token[100]; //token
    char ID[100]; //player id

    printf("Enter token: "); //ask user for token input
    scanf("%s", token);

    printf("Enter Player ID: "); //ask user for player id input
    scanf("%s", ID);

    curl = curl_easy_init();
    if(curl) {
        char url[200];
        sprintf(url, "https://stats.olympus-entertainment.com/api/v3.0/players/?player_ids=%s", ID); //add player   id to url

        struct curl_slist *headers = NULL;
        char auth_header[100];
        sprintf(auth_header, "Authorization: Token %s", token);
        headers = curl_slist_append(headers, auth_header);
        headers = curl_slist_append(headers, "accept: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        res = curl_easy_perform(curl);

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    return 0;
}