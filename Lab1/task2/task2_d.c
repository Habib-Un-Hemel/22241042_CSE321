#include <stdio.h>
#include <string.h>

int main() {
    char email[100];
    const char *oldDomain = "@kaaj.com";
    const char *newDomain = "@sheba.xyz";
    printf("Enter an email address: ");
    scanf("%s", email);
    
    size_t emailLen = strlen(email);
    size_t oldDomainLen = strlen(oldDomain);
    size_t newDomainLen = strlen(newDomain);
    
    
    if (emailLen >= oldDomainLen && strcmp(email + emailLen - oldDomainLen, oldDomain) == 0) {
        printf("Email address is outdated\n");
    }
    else if (emailLen >= newDomainLen && strcmp(email + emailLen - newDomainLen, newDomain) == 0) {
        printf("Email address is okay\n");
    }
    else {
        printf("Invalid\n");
    }
    
    return 0;
}
