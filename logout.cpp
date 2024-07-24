#include <iostream>
#include <ctime>
using namespace std;

int main() {
    // Get the current time, then subtract enough time to ensure the cookie is in the past
    time_t now = time(0);
    struct tm tm = *gmtime(&now);
    tm.tm_hour -= 1; // Subtract 1 hour from the current time
    char buf[128];
    strftime(buf, sizeof buf, "%a, %d %b %Y %H:%M:%S GMT", &tm);

    // Set the HTTP headers
    cout << "Content-type: text/html\r\n";
    cout << "Set-Cookie: name=; Expires=" << buf << "; Path=/; HttpOnly\r\n";
    cout << "Location: ./index.cgi\r\n"; // Redirect back to the home page or login page
    cout << "\r\n";

    return 0;
}