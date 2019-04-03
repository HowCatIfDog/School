
int request_resources(int customer_num, int request[]);
int release_resources(int customer_num, int release[]);
int safety_test();
int update_need(int need[][NUMBER_OF_RESOURCES],
    int allocation[][NUMBER_OF_RESOURCES],
    int maximum[][NUMBER_OF_RESOURCES]);
void print_table(int need[][NUMBER_OF_RESOURCES],
    int allocation[][NUMBER_OF_RESOURCES],
    int maximum[][NUMBER_OF_RESOURCES],
    int available[]);
int initialize_arrays(int maximum[][NUMBER_OF_RESOURCES],
    int allocation[][NUMBER_OF_RESOURCES],
    int need[][NUMBER_OF_RESOURCES]);
