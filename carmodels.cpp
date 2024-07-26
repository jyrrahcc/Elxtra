#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <utility>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <cmath>
using namespace std;

// Function to format double to string currency with commas and 2 decimal places
string formatCurrency(double amount) {
    string currency = to_string(amount);
    size_t decimalPos = currency.find(".");
    if (decimalPos != string::npos && currency.length() - decimalPos > 3) {
        currency = currency.substr(0, decimalPos + 3);
    }
    for (int i = decimalPos - 3; i > 0; i -= 3) {
        currency.insert(i, ",");
    }
    return currency;
}

class Car {
private:
    string model;
    string tag;
    string description;
    string features;
    string color;
    string imageUrl;
    string originUrl;
    string interiorUrl;
    int year;
    double price; // in PHP
    double batteryCapacity; // in kWh
    double range; // in kilometers
    double chargingTime; // in hours
    double motorPower; // in kW
    double acceleration; // 0 to 60 kph time (seconds)
    double topSpeed; // in kph

public:
    // Constructor
    Car(const string& mdl, const string& t, const string& desc,
        const string& feat, const string& col, const string& imgUrl, const string& orgUrl, const string& itrUrl, int yr, double pr,
        double batCap, double rng, double chargeTime, double mPower,
        double accel, double tSpeed)
        : model(mdl), tag(t), description(desc), features(feat), color(col), imageUrl(imgUrl),
        originUrl(orgUrl), interiorUrl(itrUrl), year(yr), price(pr), batteryCapacity(batCap), range(rng),
        chargingTime(chargeTime), motorPower(mPower), acceleration(accel),
        topSpeed(tSpeed) {}

    // Member function to display car card
    void displayCard() const {
        cout << "<a href=\"?model=" << tag << "\" class=\"row d-flex align-items-center card-display justify-content-center p-4 w-100 text-light position-relative\">";
        cout << "<section class=\"text-shadow z-index animate col-lg-4 d-flex justify-content-center flex-column fade-left\">";
        cout << "<h3 class=\"display-5\">" << model << "</h3>";
        cout << "<p class=\"fw-bold fs-4\">" << "₱" << formatCurrency(price) << "</p>";
        cout << "<p class=\"lead\">" << description << "</p>";
        cout << "</section>";
        cout << "<section class=\"col-lg-8 d-flex align-items-center z-index\">";
        cout << "<img src=\"" << imageUrl << "\" class=\"animate fade-right card-img\" alt=\"" << model << "\">";
        cout << "</section>";
        cout << "<section class=\"card-circle border border-light animate fade-up bg-dark\"> </section>";
        cout << "</a>";
    }

    // Member function to display car details
    void displayDetails() const {
        cout << "<div class=\"container-fluid bg-dark py-3 text-light\">";
            cout << "<div class=\"row\">";
                cout << "<div class=\"col-md-7 d-flex align-items-center justify-content-center\">";
                cout << "<div id=\"carouselExampleIndicators\" class=\"shadow rounded-3 rounded carousel slide bg-light\" data-bs-ride=\"carousel\">";
                cout << "<ol class=\"carousel-indicators\">";
                cout << "<li data-bs-target=\"#carouselExampleIndicators\" data-bs-slide-to=\"0\" class=\"active\"></li>";
                cout << "<li data-bs-target=\"#carouselExampleIndicators\" data-bs-slide-to=\"1\"></li>";
                cout << "</ol>";
                cout << "<div class=\"carousel-inner\">";
                cout << "<div class=\"carousel-item active\">";
                cout << "<img src=\"" << originUrl << "\" class=\"d-block w-100\" alt=\"" << model << "\" style=\"height: 100%;\">";
                cout << "</div>";
                cout << "<div class=\"carousel-item\">";
                cout << "<img src=\"" << interiorUrl << "\" class=\"d-block w-100\" alt=\"Interior\" style=\"height: 100%;\">";
                cout << "</div>";
                cout << "</div>";
                cout << "<a class=\"carousel-control-prev\" href=\"#carouselExampleIndicators\" role=\"button\" data-bs-slide=\"prev\">";
                cout << "<span class=\"carousel-control-prev-icon\" aria-hidden=\"true\"></span>";
                cout << "<span class=\"visually-hidden\">Previous</span>";
                cout << "</a>";
                cout << "<a class=\"carousel-control-next\" href=\"#carouselExampleIndicators\" role=\"button\" data-bs-slide=\"next\">";
                cout << "<span class=\"carousel-control-next-icon\" aria-hidden=\"true\"></span>";
                cout << "<span class=\"visually-hidden\">Next</span>";
                cout << "</a>";
                cout << "</div>";
            cout << "</div>";
            cout << "<div class=\"col-md-5 p-3 d-flex justify-content-center flex-column\">";
                cout << "<h2 class=\"display-4\">" << model << "</h2>";
                cout << "<p class=\"lead\">" << description << "</p>";
                cout << "<p class=\"fs-5 fw-bold\">" << "₱" <<  formatCurrency(price) << " <span class=\"fs-6 text-muted\">(Including VAT and other fees.)</span></p>";
                cout << "<p><strong>Color:</strong> " << color << "</p>";
                cout << "<p><strong>Year:</strong> " << year << "</p>";
                cout << "<p><strong>Features:</strong> " << features << "</p>";
                cout << "<a href=\"./carmodels.cgi\" class=\"mb-3 btn btn-outline-danger text-light fw-bold\">Check Other Models</a>";
                cout << "<a href=\"./contactus.cgi\" class=\"btn btn-outline-danger bg-light text-dark fw-bold\">Order Now</a>";
            cout << "</div>";
            cout << "</div>";
        cout << "</div>";
        cout << "<div class=\"w-100 sandp py-5 text-light\">";
        cout << "<div class=\"container\">";
        cout << "<div class=\"row\">";
        cout << "<div class=\"col-md-6 p-3\">";
        cout << "<h4 class=\"fw-bold\">Specifications</h4>";
        cout << "<div class=\"card mb-3\">";
        cout << "<div class=\"card-body d-flex flex-row-reverse\">";
        cout << "<i class=\"fas fa-battery-half fs-3 ms-3\"></i>";
        cout << "<div class=\"d-flex flex-grow-1 justify-content-between\">";
        cout << "<h5 class=\"card-title\">Battery Capacity</h5>";
        cout << "<p class=\"card-text\">" << batteryCapacity << " kWh</p>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "<div class=\"card mb-3\">";
        cout << "<div class=\"card-body d-flex flex-row-reverse\">";
        cout << "<i class=\"fas fa-tachometer-alt fs-3 ms-3\"></i>";
        cout << "<div class=\"d-flex flex-grow-1 justify-content-between\">";
        cout << "<h5 class=\"card-title\">Range</h5>";
        cout << "<p class=\"card-text\">" << range << " kilometers</p>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "<div class=\"card mb-3\">";
        cout << "<div class=\"card-body d-flex flex-row-reverse\">";
        cout << "<i class=\"fas fa-clock fs-3 ms-3\"></i>";
        cout << "<div class=\"d-flex flex-grow-1 justify-content-between\">";
        cout << "<h5 class=\"card-title\">Charging Time</h5>";
        cout << "<p class=\"card-text\">" << chargingTime << " hours</p>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "<div class=\"col-md-6 p-3\">";
        cout << "<h4 class=\"fw-bold\">Performance</h4>";
        cout << "<div class=\"card mb-3\">";
        cout << "<div class=\"card-body d-flex flex-row-reverse\">";
        cout << "<i class=\"fas fa-bolt fs-3 ms-3\"></i>";
        cout << "<div class=\"d-flex flex-grow-1 justify-content-between\">";
        cout << "<h5 class=\"card-title\">Motor Power</h5>";
        cout << "<p class=\"card-text\">" << motorPower << " kW</p>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "<div class=\"card mb-3\">";
        cout << "<div class=\"card-body d-flex flex-row-reverse\">";
        cout << "<i class=\"fas fa-stopwatch fs-3 ms-3\"></i>";
        cout << "<div class=\"d-flex flex-grow-1 justify-content-between\">";
        cout << "<h5 class=\"card-title\">Acceleration</h5>";
        cout << "<p class=\"card-text\">" << acceleration << " seconds (0 to 60 kph)</p>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "<div class=\"card mb-3\">";
        cout << "<div class=\"card-body d-flex flex-row-reverse\">";
        cout << "<i class=\"fas fa-tachometer-alt fs-3 ms-3\"></i>";
        cout << "<div class=\"d-flex flex-grow-1 justify-content-between\">";
        cout << "<h5 class=\"card-title\">Top Speed</h5>";
        cout << "<p class=\"card-text\">" << topSpeed << " kph</p>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
        cout << "</div>";
    }

    // Getters
    string getModel() const { return model; }
    string getTag() const { return tag; }
    string getDescription() const { return description; }
    string getFeatures() const { return features; }
    string getColor() const { return color; }
    string getImageUrl() const { return imageUrl; }
    string getOriginUrl() const { return originUrl; }
    string getInteriorUrl() const { return interiorUrl; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
    double getBatteryCapacity() const { return batteryCapacity; }
    double getRange() const { return range; }
    double getChargingTime() const { return chargingTime; }
    double getMotorPower() const { return motorPower; }
    double getAcceleration() const { return acceleration; }
    double getTopSpeed() const { return topSpeed; }
};

// Function to decode URL-encoded strings
string urlDecode(const string& str) {
    string result;
    char hex[3] = {0};
    for (size_t i = 0; i < str.length(); ++i) {
        if (str[i] == '%') {
            if (i + 2 < str.length()) {
                hex[0] = str[i + 1];
                hex[1] = str[i + 2];
                result += static_cast<char>(strtol(hex, nullptr, 16));
                i += 2;
            }
        } else if (str[i] == '+') {
            result += ' ';
        } else {
            result += str[i];
        }
    }
    return result;
}

// Function to parse query string into a key-value map
map<string, string> parseQueryString(const string& query) {
    map<string, string> params;
    string key, value;
    istringstream queryStream(query);
    while (getline(queryStream, key, '=')) {
        if (getline(queryStream, value, '&')) {
            params[urlDecode(key)] = urlDecode(value);
        }
    }
    return params;
}

// Helper function to convert a string to lowercase
string toLower(const string& input) {
    string output = input;
    transform(output.begin(), output.end(), output.begin(),
        [](unsigned char c){ return tolower(c); });
    return output;
}

// Function to parse cookies
map<string, string> parse_cookies(const string &cookie_header) {
    map<string, string> cookies;
    size_t pos = 0;
    string token;
    string header = cookie_header;
    while ((pos = header.find("; ")) != string::npos) {
        token = header.substr(0, pos);
        size_t eq_pos = token.find("=");
        if (eq_pos != string::npos) {
            string key = token.substr(0, eq_pos);
            string value = token.substr(eq_pos + 1);
            cookies[key] = value;
        }
        header.erase(0, pos + 2);
    }
    if ((pos = header.find("=")) != string::npos) {
        string key = header.substr(0, pos);
        string value = header.substr(pos + 1);
        cookies[key] = value;
    }
    return cookies;
}

int main() {
    // Read the contents of the style sheet file
    ifstream styleSheetFile("./styles.css");
    string styleSheetContent((istreambuf_iterator<char>(styleSheetFile)), istreambuf_iterator<char>());
    styleSheetFile.close();
    // Car database
    vector<Car> carDatabase;
    // Model not found content
    string modelNotFoundContent = R"(<section class="container py-5">
        <h2 class="display-4 text-light">Model not found.</h2>
        <a href="./carmodels.cgi" class="btn btn-light text-dark">Back to Car Models</a>
    </section>)";

    // Populate the car database using unique Elxtra Motors, An electric car company, 5 car models
    // ZenithEon
    carDatabase.emplace_back("ZenithEon", "zenitheon",
        "The ZenithEon represents a new era of electric mobility, blending elegant design with cutting-edge technology.",
        "Autopilot, Full Self-Driving Capability, Over-the-Air Software Updates, Premium Connectivity",
        "Pearl White", "https://scontent-mnl1-2.xx.fbcdn.net/v/t1.15752-9/451011914_790471106591407_5712580914768615546_n.png?_nc_cat=102&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeHAlzGUpIotRvoTiCDaZAOmowF4oWVbLx6jAXihZVsvHqIWeb1yw6Glrn9Pgyh0EQUeSeO5tynT1qEpH1jMiGg7&_nc_ohc=vxFmQRl4LV8Q7kNvgHe2TJj&_nc_ht=scontent-mnl1-2.xx&oh=03_Q7cD1QGU01F5Pe2mWXAN4tfv4FY8W71ViTYwOiRKoCAH9jDWnA&oe=66C5B5D1",
        "https://scontent.fmnl9-1.fna.fbcdn.net/v/t1.15752-9/452149569_1019766789734981_4554600585309120314_n.png?_nc_cat=111&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeHUYAOozcQCUzK0WbclKVtOtUYc8BHNpda1RhzwEc2l1nIXHnFFNNsxaZVpuezafLK7RWSCZDa855ODh-nMclYn&_nc_ohc=7hP7cZ8y5FYQ7kNvgEwzL91&_nc_ht=scontent.fmnl9-1.fna&oh=03_Q7cD1QFvnWp2v_vJczq_M0D3pUw3HUkIrRABpGdiaz2N1uKrWg&oe=66C6AF83", 
        "https://scontent.fmnl9-2.fna.fbcdn.net/v/t1.15752-9/451430229_505213985308507_609299101154432417_n.png?_nc_cat=101&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeHfEuqs4DyTHe5-k7agQPa8PuQ7jukneMA-5DuO6Sd4wPTqOCmDS44dqQulInUz6T2HicQHCvwJ3R0iHNCO9qPZ&_nc_ohc=ZHIW96nO74AQ7kNvgHUUMpw&_nc_ht=scontent.fmnl9-2.fna&oh=03_Q7cD1QH6oPEMNfUAPsI8EekV761Ix-O-wr4Ee5rKjSHHfh-UYQ&oe=66C67DE2", 2023, 1500000.0, 80.0, 400.0, 8.0, 200.0, 6.0, 180.0);

    // QuantumX
    carDatabase.emplace_back("QuantumX", "quantumx",
        "The QuantumX redefines performance and luxury in the electric vehicle segment.",
        "Autopilot, Premium Sound System, Adaptive Cruise Control, Wireless Charging",
        "Midnight Black", "https://scontent-mnl1-2.xx.fbcdn.net/v/t1.15752-9/451277419_2066723507077182_1977782340440860320_n.png?_nc_cat=103&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGUKhzHpdjEN14IKX4MP9NhUIATlAc-QPdQgBOUBz5A99e6jA_GIObDPJrrhLXV41Gf_zYMAR2RRn-DifOuyjgI&_nc_ohc=N6C4Vm1TDSMQ7kNvgEiwEdY&_nc_ht=scontent-mnl1-2.xx&oh=03_Q7cD1QGOxm0y8g8k__HK-R5RNE_JnkjhQHZ5z6OojFWM0QQJOw&oe=66C5E660",
        "https://scontent.fmnl9-2.fna.fbcdn.net/v/t1.15752-9/452005070_3660568064158719_1032655168218171448_n.png?_nc_cat=107&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGuVjHdIvrwDneWHeorc9Xp2I25vgIRROfYjbm-AhFE51NJaiZ46iwHUVLGWuTmHrgHQnp2XsfDPH3k4VGIzHbb&_nc_ohc=BTwJmF-fdCsQ7kNvgEC4qR_&_nc_ht=scontent.fmnl9-2.fna&oh=03_Q7cD1QGBykqdXf6U9Fm-LTLmh3WThNot1M7eazkAzUbID4dPlQ&oe=66C69B85", 
        "https://scontent.fmnl9-4.fna.fbcdn.net/v/t1.15752-9/451696834_1125964695158533_6502086880406349766_n.png?_nc_cat=108&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeEN8LZUHjiNGYomBwgerXn6sD4ho7lSqEOwPiGjuVKoQ3Ln4R8aeSyUNviDJbyDYMdJq1XzHI-lvOBRRaOy4hvg&_nc_ohc=bxDXGB0Q7Y4Q7kNvgHWbfKB&_nc_ht=scontent.fmnl9-4.fna&oh=03_Q7cD1QHOSp8Xv158w5CMuU14v0wNlu0GZv6zUniMCMY2NJ0efw&oe=66C6A36B", 2024, 2000000.0, 100.0, 500.0, 5.0, 300.0, 4.0, 220.0);

    // Luminova
    carDatabase.emplace_back("Luminova", "luminova",
        "The Luminova combines elegance with sustainability.",
        "Regenerative Braking, Panoramic Sunroof, Voice-Activated Controls",
        "Lunar Gray", "https://scontent-mnl1-2.xx.fbcdn.net/v/t1.15752-9/451439136_996205265569745_5457821148225663634_n.png?_nc_cat=105&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeFFKor_dEE9unA1JO1ONuGxYq12CdfhMm9irXYJ1-Eyb_I6ArNe1H1zaCWbY151lE_luMZOXxospd7FMZBdugBx&_nc_ohc=37PLU_4UPewQ7kNvgH0oucZ&_nc_ht=scontent-mnl1-2.xx&oh=03_Q7cD1QFRVLdBMpDwnZMfhWHFUutjl2gt_Y1oCg0DJc70jJ1Drg&oe=66C5B799",
        "https://scontent.fmnl9-2.fna.fbcdn.net/v/t1.15752-9/451323495_980882510498645_6282516183590098653_n.png?_nc_cat=103&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeF6IocKd6cEDRFzsZZaL4jDROn-X2QTXrhE6f5fZBNeuHyyrKBIiusxajbbWOnMopnNVh3uThOw49CobGF0I70Q&_nc_ohc=q_ZMC5SuPKYQ7kNvgHu-sk_&_nc_ht=scontent.fmnl9-2.fna&oh=03_Q7cD1QHgcCYr4BxrM9AgPA4FZjbhGcTpcsrbKsCU191scHNjwA&oe=66C6AC5A", 
        "https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/449903868_966513365252907_4497279307927428392_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeEKW95hOp52422FDJyK-MDA_OXs3qO3MkL85ezeo7cyQkE4rW3eMoj5rq3qDlLw8qY9_9a164ZfqFlJlLVHDldp&_nc_ohc=s3wnXNsFMhoQ7kNvgHwuJT4&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QER1gAOJBAzUsITOPi_IjS0ENDiMHyPwASEwZ_CddipxQ&oe=66C6908C", 2023, 1200000.0, 60.0, 300.0, 6.0, 150.0, 7.0, 160.0);

    // Nextron
    carDatabase.emplace_back("Nextron", "nextron",
        "The Nextron is a versatile electric crossover designed for practicality and efficiency.",
        "Lane-Keeping Assist, Touchscreen Infotainment, Rearview Camera",
        "Electric Blue", "https://scontent-mnl1-2.xx.fbcdn.net/v/t1.15752-9/451390842_884947063460453_415468250194106051_n.png?_nc_cat=103&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeHRcjLwf5HOJthxFdUSIUjtGLiRWIK0KYsYuJFYgrQpi-mH2PYcClx3bbPKa6loZ99ycCela5VcKz_zGj3jhQfL&_nc_ohc=Sg_Mad0t43IQ7kNvgHLEWg9&_nc_ht=scontent-mnl1-2.xx&oh=03_Q7cD1QHairuJdaNMj5JEAXi5HZL8_WLrkP55-umqzDv4OChYyQ&oe=66C5E4E6",
        "https://scontent.fmnl9-4.fna.fbcdn.net/v/t1.15752-9/451446924_472374362080556_4382954125856774196_n.png?_nc_cat=106&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeEcWjJxPiVo24QzOLaXip-AmtWinT7K4wKa1aKdPsrjAuqoiPSvlxQ6ptQNIgbR4a9wdQjnrkHyWzrVuXHm5Dh1&_nc_ohc=XhkOEz18Za4Q7kNvgF_O8jY&_nc_ht=scontent.fmnl9-4.fna&oh=03_Q7cD1QE6LaB-8V6IT1nkCW0Dd8YH5qKt_3pZAnhQLWqXH74Zfg&oe=66C69843", 
        "https://scontent.fmnl9-4.fna.fbcdn.net/v/t1.15752-9/451622259_1894112094343955_2371808051181805584_n.png?_nc_cat=108&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeG7RoxsSzEINUtyTRox0IQ62ykjdw2_44HbKSN3Db_jgU5aGdIe72p9fty3JZTlGb6ZRFMVWlA8u-mM-a00ZuOA&_nc_ohc=cZaIseKgQL4Q7kNvgGqiIUV&_nc_ht=scontent.fmnl9-4.fna&oh=03_Q7cD1QEVUYbddmEPN6SeMwOMdeRusXxLAqV5E2UDBPxKETXTZw&oe=66C689D5", 2022, 1000000.0, 50.0, 250.0, 4.0, 120.0, 8.0, 150.0);

    // Print the HTTP header
    cout << "Content-Type: text/html\r\n\r\n";

    string requestMethod = getenv("REQUEST_METHOD");
    // Read environment variables for cookie and query string
    string cookie_header = getenv("HTTP_COOKIE") ? getenv("HTTP_COOKIE") : "";
    map<string, string> cookies = parse_cookies(cookie_header);
    string name;
    // Check if the user is logged in
    if (cookies.find("name") != cookies.end()) {
        name = cookies["name"];
    }

    string userDisplay = "<div class=\"d-flex align-items-center text-light gap-3\">" + 
    (cookies.find("name") != cookies.end() ? 
          ("<div class='dropdown'>"
                "<button class='btn btn-outline-danger text-light fw-bold border-light dropdown-toggle' type='button' id='dropdownUser' data-bs-toggle='dropdown' aria-haspopup='true' aria-expanded='false'>" + 
                name +
                "</button>"
                "<div class='dropdown-menu dropdown-menu-end' aria-labelledby='dropdownUser'>"
                    "<a class='dropdown-item' href='./carloancalculator.cgi'>Car Loan Calculator</a>"
                    "<a class='dropdown-item' href='./userprofile.cgi'>User Profile</a>"
                    "<a class='dropdown-item' href='./logout.cgi'>Logout</a>"
                "</div>"
          "</div>") 
    : 
          "<a href='./login.cgi' class='btn btn-outline-danger text-light fw-bold border-light'>Login</a>") 
    + "</div>";

    // Print the HTML content
    cout << R"(<!DOCTYPE html>
    <html lang="en">
        <head>
        <!-- Document Metadata -->
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
        <meta name="author" content="John Yrrah Cabiles">

        <!-- Favicon and Styles -->
        <link rel="icon" type="image/x-icon" href="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A">
        <style>)" + styleSheetContent + R"(</style>

        <!-- Bootstrap CSS -->
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
        <link rel="stylesheet" href="https://pro.fontawesome.com/releases/v5.10.0/css/all.css" integrity="sha384-AYmEC3Yw5cVb3ZcuHtOA93w35dYTsvhLPVnYs9eStHfGJvOvKxVfELGroGkvsg+p" crossorigin="anonymous"/>

        <!-- Page Title -->
        <title>Car Models - Elxtra Motors</title>
    </head>
    <body>
        <!-- Navbar -->
      <header id="navbar" class="fixed-top header navbar navbar-expand-lg navbar-dark fade-down">
        <div class="container-fluid">
          <a class="navbar-brand d-flex align-items-center" href="#">
            <img src="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A" alt="" width="30" height="24" class="d-inline-block align-text-top">
            <h1 class="display-4 fs-4 m-3">Elxtra</h1>
          </a>
          <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
          <span class="navbar-toggler-icon"></span>
          </button>
          <nav class="collapse navbar-collapse" id="navbarSupportedContent">
            <ul class="navbar-nav me-auto">
                <li class="nav-item">
                    <a class="nav-link p-0 m-3" href="./index.cgi">Home</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link p-0 m-3" href="./aboutus.cgi">About Us</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link p-0 m-3" href="./contactus.cgi">Contact Us</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link p-0 m-3 active" aria-current="page" href="./carmodels.cgi">Car Models</a>
                </li>
                </ul>
                <div class="d-flex justify-content-between align-items-center gap-3">
                <form method="post" class="form-inline flex-grow-1">
                    <section class="input-group">
                        <input class="form-control " type="search" placeholder="Search Car Model..." name="model" aria-label="Search" required>
                        <button class="btn btn-outline-danger border border-light text-light" type="submit"><i class="fas fa-search"></i></button>
                    </section>
                </form>)" + userDisplay + R"(</div></nav>
        </div>
      </header>
        <main>
        <!-- Header Section -->
        <section class="cover2">
            <section class="darkener boundary2 py-5 w-100 d-flex align-items-center justify-content-center">
                <section class="container">
                    <section class="row">
                        <section class="col-sm-8 animate fade-left">
                            <h2 class="display-3 text-light mt-5">Car Models</h2>
                        </section>
                    </section>
                </section>
            </section>
        </section>)";
    // Display car model details or all car models page for Get Method
    if (requestMethod == "GET") {
        string queryString = getenv("QUERY_STRING");
        map<string, string> queryParams = parseQueryString(queryString);
        // Display car model details page
        if (queryParams.find("model") != queryParams.end()) {
            string modelTag = queryParams["model"];
            bool found = false;
            for (const Car& car : carDatabase) {
                if (car.getTag() == modelTag) {
                    found = true;
                    car.displayDetails();
                    cout << "<div class='bg-dark'><div class=\"container w-100 py-5 text-light\">";
                    cout << "<h2>Finance Your Dream Car with Ease</h2>";
                    cout << R"(<p class="lead">At Elxtra, we understand that purchasing a new car is a significant investment. That's why we've created the Elxtra Car Loan Calculator, a powerful tool designed to help you plan your finances and make informed decisions.</p>)";
                    if (cookies.find("name") != cookies.end()) {
                        cout << "<p class='lead'>Get started by using the Elxtra Car Loan Calculator with " << car.getModel() << " to estimate your monthly payments and find the best financing options for your budget.</p>";
                        cout << "<a href='./carloancalculator.cgi?carModel=" << car.getModel() << "' class='btn btn-outline-danger text-light fw-bold border-light'>Car Loan Calculator</a>";
                    } else {
                        cout << "<p class='lead'>You need to login first before using the Car Loan Calculator.</p>";
                        cout << "<p class='lead'>By logging in and using the Elxtra Car Loan Calculator, you'll not only get accurate loan estimates but also help us gather valuable data to improve our services and tailor our offerings to meet your needs better.</p>";
                        cout << "<a href='./login.cgi' class='btn btn-outline-danger text-light fw-bold border-light'>Login</a>";
                    }
                    cout << "</div></div>";
                    break;
                }
            }
            // Display model not found content if the model is not in the database
            if (!found) {
                cout << modelNotFoundContent;
            }
        }
        // Display all car models page 
        else {
            cout << R"(<section class="container py-5 text-light">
                <h2 class="display-5 fade-left animate text-shadow">Discover the Future of Driving with Elxtra</h2>
                <p class="lead fade-left animate">Welcome to Elxtra, where cutting-edge technology meets unparalleled performance. Our innovative car models are designed to provide an exceptional driving experience that exceeds expectations. Whether you're looking for speed, luxury, efficiency, or versatility, Elxtra has the perfect car to match your lifestyle. Explore our range of state-of-the-art electric vehicles and join us on the journey to a sustainable and exhilarating future.</p>
                <section class="d-flex align-items-center justify-content-center gap-3 flex-wrap">)";
            for (const Car& car : carDatabase) {
                car.displayCard();
            }
            cout << "</section>";
            cout << "</section>";
        }
    } 
    // Display search results page for Post Method
    else if (requestMethod == "POST") {
        string contentLengthStr = getenv("CONTENT_LENGTH");
        // Check if the content length is not empty
        if (!contentLengthStr.empty()) {
            int contentLength = stoi(contentLengthStr);
            string postBody;
            postBody.resize(contentLength);
            cin.read(&postBody[0], contentLength);
            map<string, string> postParams = parseQueryString(postBody);
            // Cbecks if the search query is not empty
            if (postParams.find("model") != postParams.end()) {
                string modelTag = postParams["model"];
                bool found = false;
                cout << R"(<section class="container py-5">
                <section class="d-flex align-items-center justify-content-center gap-3 flex-wrap">
                <h2 class="display-5 text-light animate fade text-left">Search result/s for )" << modelTag << R"(...</h2>)";
                for (const Car& car : carDatabase) {
                    if (toLower(car.getTag()).find(toLower(modelTag)) != string::npos) {
                        found = true;
                        car.displayCard();
                    }
                }
                // Display model not found content if there is no car model that matches the search query
                if (!found) {
                    cout << modelNotFoundContent;
                }
                cout << "</section>";
                cout << "</section>";
            } 
            // Display all car models page if the search query is empty
            else {
                cout << R"(<section class="container py-5 text-light">
                <h2 class="display-5 text-shadow">Discover the Future of Driving with Elxtra</h2>
                <p class="lead">Welcome to Elxtra, where cutting-edge technology meets unparalleled performance. Our innovative car models are designed to provide an exceptional driving experience that exceeds expectations. Whether you're looking for speed, luxury, efficiency, or versatility, Elxtra has the perfect car to match your lifestyle. Explore our range of state-of-the-art electric vehicles and join us on the journey to a sustainable and exhilarating future.</p>
                <section class="d-flex align-items-center justify-content-center gap-3 flex-wrap">)";
                for (const Car& car : carDatabase) {
                    car.displayCard();
                }
                cout << "</section>";
                cout << "</section>";
            }
        } 
        // Display all car models page if the content length is empty
        else {
            cout << R"(<section class="container py-5 text-light">
                <h2 class="display-5 text-shadow">Discover the Future of Driving with Elxtra</h2>
                <p class="lead">Welcome to Elxtra, where cutting-edge technology meets unparalleled performance. Our innovative car models are designed to provide an exceptional driving experience that exceeds expectations. Whether you're looking for speed, luxury, efficiency, or versatility, Elxtra has the perfect car to match your lifestyle. Explore our range of state-of-the-art electric vehicles and join us on the journey to a sustainable and exhilarating future.</p>
                <section class="d-flex align-items-center justify-content-center gap-3 flex-wrap">)";
            for (const Car& car : carDatabase) {
                car.displayCard();
            }
            cout << "</section>";
            cout << "</section>";
        }
    }

        cout << R"(</main>
        <!-- Footer Section -->
      <footer>
            <section class="w-100 container pt-5 pb-3">
                <section class="animate fade d-flex flex-column flex-sm-row align-items-center justify-content-center">
                    <section class="">
                        <img style="min-width: 75px; max-width: 100px;" src="https://scontent.fmnl9-3.fna.fbcdn.net/v/t1.15752-9/450574779_820070233598209_5547379444503085753_n.png?_nc_cat=104&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGCL7NnXUKoqxcaJEGWHvPYg0tBM1PjUZuDS0EzU-NRm7X0q5jk79pwhZnPTHinMxHk0BRUU6dSFOpXR6y4Zs6o&_nc_ohc=hQLcWxI2vNkQ7kNvgEdpQpd&_nc_ht=scontent.fmnl9-3.fna&oh=03_Q7cD1QGi2ixXMwmdWUXjErCioNdXkHryhhdrNwiz3gJ54LEjlw&oe=66C13C8A" alt="Elxtra" class="w-100 d-inline-block align-text-top">
                    </section>
                    <section class="d-md-flex align-items-center m-auto my-3">
                        <nav>
                            <ul class="d-md-flex p-0 m-0">
                            <li class="nav-item">
                                <a class="nav-link p-0 m-3 text-light" href="./index.cgi">Home</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link p-0 m-3 text-light" href="./aboutus.cgi">About Us</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link p-0 m-3 text-light" href="./contactus.cgi">Contact Us</a>
                            </li>
                            <li class="nav-item">
                                <a class="nav-link p-0 m-3 text-light" href="./carmodels.cgi">Car Models</a>
                            </li>
                            </ul>
                        </nav>
                    </section>
                    <section class="socials d-flex gap-3 align-items-center justify-content-center">
                        <a href="#" class="text-light fs-4"><i class="fab fa-facebook"></i></a>
                        <a href="#" class="text-light fs-4"><i class="fab fa-twitter"></i></a>
                        <a href="#" class="text-light fs-4"><i class="fab fa-instagram"></i></a>
                    </section>
                </section>
                <hr class="animate fade" />
                <ul class="animate fade d-flex align-items-center justify-content-center gap-3 flex-wrap">
                    <p class="m-3">© 2024 Elxtra. All rights reserved.</p>
                    <li class="nav-item">
                        <a class="nav-link p-0 m-3 text-light" href="#">Privacy Policy</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link p-0 m-3 text-light" href="#">Terms and Conditions</a>
                    </li>
                    <li class="nav-item">
                        <a class="nav-link p-0 m-3 text-light" href="#">Cookie Policy</a>
                    </li>
                </ul>
            </section>
        </footer>
      <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.9.2/dist/umd/popper.min.js" integrity="sha384-IQsoLXl5PILFhosVNubq5LC7Qb9DXgDA9i+tQ8Zj3iwWAwPtgFTxbJ8NT4GN1R8p" crossorigin="anonymous"></script>
      <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/js/bootstrap.min.js" integrity="sha384-cVKIPhGWiC2Al4u+LWgxfKTRIcfu0JTxR+EQDz/bgldoEyl4H0zUF0QKbrJ0EcQF" crossorigin="anonymous"></script>
      <script>
        const navbar = document.getElementById('navbar');

        window.addEventListener('resize', () => {
          if (window.innerWidth < 992) {
            navbar.classList.add('bg-dark');
          } else {
            navbar.classList.remove('bg-dark');
          }
        });

        window.addEventListener('scroll', () => {
          if (window.scrollY > 0) {
            navbar.classList.add('bg-dark');
            navbar.classList.add('border-darker');
          } else {
            if (window.innerWidth < 992) {
              navbar.classList.add('border-darker');
              navbar.classList.add('bg-dark');
            } else {
              navbar.classList.remove('border-darker');
              navbar.classList.remove('bg-dark');
            }
          }
        });
      </script>
        <!-- Scroll Animation Script -->
        <script>
            let observer;
            function handleIntersect(entries, observer) {
            entries.forEach(entry => {
                if (entry.isIntersecting) {
                if (entry.target.dataset.animated !== 'true') {
                    triggerAnimation(entry.target);
                    entry.target.dataset.animated = 'true';
                }
                } else {
                entry.target.dataset.animated = 'false';
                }
            });
            }
    
            function triggerAnimation(element) {
            if (element.classList.contains('fade-down')) {
                element.classList.remove('fade-down');
                void element.offsetWidth;
                element.classList.add('fade-down');
            } else if (element.classList.contains('fade-right')) {
                element.classList.remove('fade-right');
                void element.offsetWidth;
                element.classList.add('fade-right');
            } else if (element.classList.contains('fade-left')) {
                element.classList.remove('fade-left');
                void element.offsetWidth;
                element.classList.add('fade-left');
            } else if (element.classList.contains('fade-up')) {
                element.classList.remove('fade-up');
                void element.offsetWidth;
                element.classList.add('fade-up');
            } else {
                element.classList.remove('fade');
                void element.offsetWidth;
                element.classList.add('fade');
            }
            }
    
            function setupIntersectionObserver() {
            const elements = document.querySelectorAll('.animate');
            const options = {
                root: null,
                rootMargin: '80px',
                threshold: 0.1
            };
    
            observer = new IntersectionObserver(handleIntersect, options);
    
            elements.forEach(element => {
                observer.observe(element);
            });
            }
            
            document.addEventListener('DOMContentLoaded', setupIntersectionObserver);
        </script>
        </body>
    </html>)";
    
    return 0;
}