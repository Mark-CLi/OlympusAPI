#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

void Sleep(int i);

int main(void) {
    CURL *curl;
    CURLcode res;
    char token[100]; //token
    char ID[100]; //player id
    char input[100]; //user input
    printf("Welcome to some ghetto ass API Poling Tool\n"); //welcome message
    printf("MCL 2022 All right reserved, olympus-entertainment.com/profile/47738-mark_/\n"); //welcome message
    printf("Inproper use of this tool may result in a ban/other administrative action by oly Admin\n"); //Warning message

    while (1) {
        printf("Enter feature (Server/Shed-ledger/Cartels/Players) ""Caps Sensitives" "or type 'stop' to exit:  \n"); //ask user for feature input
        scanf("%s", input);

        if (strcmp(input, "stop") == 0) {
            break;
        } else {

        }

        printf("Enter token(Visit Your Gang Profile on Oly Stats,DO NOT INCLUDE token at the beginning):\n "); //ask user for token input
        scanf("%s", token);


        printf("Enter Player ID/Shed ID\n"); //ask user for player id input
        scanf("%s", ID);

        int i;

        for (i = 0; ID[i] != '\0'; i++) {
            if (!isdigit(ID[i])) {
               printf("you did not enter a number,Below is message from API... exiting now(15s)\n");
               break;
           } else {
               printf("Gathering Date Now...\n");
           }
       }

        curl = curl_easy_init(); //initialize curl
        if(curl) { //if curl is initialized
            char url[200];
            if (strcmp(input, "Server") == 0) {
                sprintf(url, "https://stats.olympus-entertainment.com/api/v3.0/servers/");
            } else if (strcmp(input, "Shed-ledger") == 0) {
                sprintf(url, "https://stats.olympus-entertainment.com/api/v3.0/shed_ledger/?player_ids=%s", ID);
            } else if (strcmp(input, "Cartels") == 0) {
                sprintf(url, "https://stats.olympus-entertainment.com/api/v3.0/cartels/");
            } else if (strcmp(input, "Players") == 0) {
                sprintf(url, "https://stats.olympus-entertainment.com/api/v3.0/players/?player_ids=%s", ID);
            } else {
                printf("Invalid input\n");
                continue;
            }

            struct curl_slist *headers = NULL;
            char auth_header[100];
            sprintf(auth_header, "Authorization: Token %s", token);
            headers = curl_slist_append(headers, auth_header);
            headers = curl_slist_append(headers, "accept: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

            res = curl_easy_perform(curl);

            if(res != CURLE_OK) {
                fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            } else {
                char *output_str;
                long http_code = 0;
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
                if (http_code == 200) {
                    curl_easy_getinfo(curl, CURLINFO_CONTENT_TYPE, &output_str);
                    if (strstr(output_str, "application/json")) {
                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fwrite);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, stdout);
                        curl_easy_setopt(curl, CURLOPT_HEADER, 0);

                        size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata) {
                            size_t num_bytes = size * nmemb;
                            char *comma_pos = strchr(ptr, ',');
                            while (comma_pos != NULL) {
                                printf("%.*s\n", (int)(comma_pos - ptr + 1), ptr);
                                ptr = comma_pos + 1;
                                comma_pos = strchr(ptr, ',');
                            }
                            if (*ptr != '\0') {
                                printf("%s", ptr);
                            }
                            return num_bytes;
                        }
                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
                        res = curl_easy_perform(curl);
                    }
                }
            }
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);
        }
        printf("\n");
    }

    return 0;
}



