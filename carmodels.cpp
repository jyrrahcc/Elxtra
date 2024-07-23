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
using namespace std;

class Car {
private:
    string model;
    string tag;
    string description;
    string features;
    string color;
    string imageUrl;
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
        const string& feat, const string& col, const string& imgUrl, int yr, double pr,
        double batCap, double rng, double chargeTime, double mPower,
        double accel, double tSpeed)
        : model(mdl), tag(t), description(desc), features(feat), color(col), imageUrl(imgUrl),
        year(yr), price(pr), batteryCapacity(batCap), range(rng),
        chargingTime(chargeTime), motorPower(mPower), acceleration(accel),
        topSpeed(tSpeed) {}

    // Getters
    string getModel() const { return model; }
    string getTag() const { return tag; }
    string getDescription() const { return description; }
    string getFeatures() const { return features; }
    string getColor() const { return color; }
    string getImageUrl() const { return imageUrl; }
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

int main() {
    // Read the contents of the style sheet file
    ifstream styleSheetFile("./styles.css");
    string styleSheetContent((istreambuf_iterator<char>(styleSheetFile)), istreambuf_iterator<char>());
    styleSheetFile.close();

    vector<Car> carDatabase;
    string mainContent;
    string modelNotFoundContent = R"(<section class="container py-5">
        <form method="post" class="input-group mb-3">
            <input class="form-control bg-dark shadow-light text-light" type="search" placeholder="Search Model..." name="model" aria-label="Search" required>
            <button class="btn btn-dark border border-light text-light input-group-text" type="submit"><i class="fas fa-search"></i></button>
        </form>
        <h2 class="display-4 text-light">Model not found.</h2>
        <a href="./carmodels.cgi" class="btn btn-light text-dark">Back to Car Models</a>
    </section>)";

    // Populate the car database using unique Elxtra Motors, An electric car company, 5 car models
    // ZenithEon
    carDatabase.emplace_back("ZenithEon", "zenitheon",
        "The ZenithEon represents a new era of electric mobility, blending elegant design with cutting-edge technology.",
        "Autopilot, Full Self-Driving Capability, Over-the-Air Software Updates, Premium Connectivity",
        "Pearl White", "https://scontent-mnl1-2.xx.fbcdn.net/v/t1.15752-9/451011914_790471106591407_5712580914768615546_n.png?_nc_cat=102&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeHAlzGUpIotRvoTiCDaZAOmowF4oWVbLx6jAXihZVsvHqIWeb1yw6Glrn9Pgyh0EQUeSeO5tynT1qEpH1jMiGg7&_nc_ohc=vxFmQRl4LV8Q7kNvgHe2TJj&_nc_ht=scontent-mnl1-2.xx&oh=03_Q7cD1QGU01F5Pe2mWXAN4tfv4FY8W71ViTYwOiRKoCAH9jDWnA&oe=66C5B5D1",
        2023, 1500000.0, 80.0, 400.0, 8.0, 200.0, 6.0, 180.0);

    // QuantumX
    carDatabase.emplace_back("QuantumX", "quantumx",
        "The QuantumX redefines performance and luxury in the electric vehicle segment.",
        "Autopilot, Premium Sound System, Adaptive Cruise Control, Wireless Charging",
        "Midnight Black", "https://scontent-mnl1-2.xx.fbcdn.net/v/t1.15752-9/451277419_2066723507077182_1977782340440860320_n.png?_nc_cat=103&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeGUKhzHpdjEN14IKX4MP9NhUIATlAc-QPdQgBOUBz5A99e6jA_GIObDPJrrhLXV41Gf_zYMAR2RRn-DifOuyjgI&_nc_ohc=N6C4Vm1TDSMQ7kNvgEiwEdY&_nc_ht=scontent-mnl1-2.xx&oh=03_Q7cD1QGOxm0y8g8k__HK-R5RNE_JnkjhQHZ5z6OojFWM0QQJOw&oe=66C5E660",
        2024, 2000000.0, 100.0, 500.0, 5.0, 300.0, 4.0, 220.0);

    // Luminova
    carDatabase.emplace_back("Luminova", "luminova",
        "The Luminova combines elegance with sustainability.",
        "Regenerative Braking, Panoramic Sunroof, Voice-Activated Controls",
        "Lunar Gray", "https://scontent-mnl1-2.xx.fbcdn.net/v/t1.15752-9/451439136_996205265569745_5457821148225663634_n.png?_nc_cat=105&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeFFKor_dEE9unA1JO1ONuGxYq12CdfhMm9irXYJ1-Eyb_I6ArNe1H1zaCWbY151lE_luMZOXxospd7FMZBdugBx&_nc_ohc=37PLU_4UPewQ7kNvgH0oucZ&_nc_ht=scontent-mnl1-2.xx&oh=03_Q7cD1QFRVLdBMpDwnZMfhWHFUutjl2gt_Y1oCg0DJc70jJ1Drg&oe=66C5B799",
        2023, 1200000.0, 60.0, 300.0, 6.0, 150.0, 7.0, 160.0);

    // Nextron
    carDatabase.emplace_back("Nextron", "nextron",
        "The Nextron is a versatile electric crossover designed for practicality and efficiency.",
        "Lane-Keeping Assist, Touchscreen Infotainment, Rearview Camera",
        "Electric Blue", "https://scontent-mnl1-2.xx.fbcdn.net/v/t1.15752-9/451390842_884947063460453_415468250194106051_n.png?_nc_cat=103&ccb=1-7&_nc_sid=9f807c&_nc_eui2=AeHRcjLwf5HOJthxFdUSIUjtGLiRWIK0KYsYuJFYgrQpi-mH2PYcClx3bbPKa6loZ99ycCela5VcKz_zGj3jhQfL&_nc_ohc=Sg_Mad0t43IQ7kNvgHLEWg9&_nc_ht=scontent-mnl1-2.xx&oh=03_Q7cD1QHairuJdaNMj5JEAXi5HZL8_WLrkP55-umqzDv4OChYyQ&oe=66C5E4E6",
        2022, 1000000.0, 50.0, 250.0, 4.0, 120.0, 8.0, 150.0);

    // Print the HTTP header
    cout << "Content-Type: text/html\r\n\r\n";

    string requestMethod = getenv("REQUEST_METHOD");

    // Get and Post Methods with search functionality

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
        <header id="navbar" class="animate fixed-top navbar navbar-expand-xl navbar-dark fade-down">
            <div class="container-fluid">
                <a class="navbar-brand d-flex gap-3 align-items-center" href="./index.cgi">
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
                    <a class="nav-link p-0 m-3" href="./contactus.cgi" tabindex="-1" aria-disabled="true">Contact Us</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link p-0 m-3" href="./faqs.cgi" tabindex="-1" aria-disabled="true">FAQs</a>
                </li>
                <li class="nav-item">
                    <a class="nav-link p-0 m-3 active" aria-current="page" href="./carmodels.cgi" tabindex="-1" aria-disabled="true">Car Models</a>
                </li>
                </ul>
                <form method="post" class="form-inline">
                    <section class="input-group">
                        <input class="form-control" type="search" placeholder="Search Car Model..." name="model" aria-label="Search" required>
                        <button class="btn btn-outline-danger border border-light text-light" type="submit"><i class="fas fa-search"></i></button>
                    </section>
                </form>
                <div class="d-flex">
                <a href="./login.cgi" class="btn m-3 btn-outline-danger text-light fw-bold border-light">Login</a>
                </div>
            </nav>
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
        
    if (requestMethod == "GET") {
        string queryString = getenv("QUERY_STRING");
        map<string, string> queryParams = parseQueryString(queryString);
        if (queryParams.find("model") != queryParams.end()) {
            string modelTag = queryParams["model"];
            bool found = false;
            for (const Car& car : carDatabase) {
                if (car.getTag() == modelTag) {
                    found = true;
                    cout << "<h1>" << car.getModel() << "</h1>";
                    cout << "<p><strong>Description:</strong> " << car.getDescription() << "</p>";
                    cout << "<p><strong>Features:</strong> " << car.getFeatures() << "</p>";
                    cout << "<p><strong>Color:</strong> " << car.getColor() << "</p>";
                    cout << "<p><strong>Year:</strong> " << car.getYear() << "</p>";
                    cout << "<p><strong>Price:</strong> $" << car.getPrice() << "</p>";
                    cout << "<p><strong>Battery Capacity:</strong> " << car.getBatteryCapacity() << " kWh</p>";
                    cout << "<p><strong>Range:</strong> " << car.getRange() << " miles</p>";
                    cout << "<p><strong>Charging Time:</strong> " << car.getChargingTime() << " hours</p>";
                    cout << "<p><strong>Motor Power:</strong> " << car.getMotorPower() << " kW</p>";
                    cout << "<p><strong>Acceleration:</strong> " << car.getAcceleration() << " seconds (0 to 60 mph)</p>";
                    cout << "<p><strong>Top Speed:</strong> " << car.getTopSpeed() << " mph</p>";
                    break;
                }
            }
            if (!found) {
                cout << modelNotFoundContent;
            }
        } else {
            cout << R"(<section class="container py-5">
                <section class="d-flex align-items-center justify-content-center gap-3 flex-wrap">)";
            for (const Car& car : carDatabase) {
                    cout << "<a href=\"?model=" << car.getTag() << "\" class=\"row d-flex align-items-center card-display justify-content-center p-4 w-100 text-light position-relative\">";
                        cout << "<section class=\"z-index animate col-lg-4 d-flex justify-content-center flex-column fade-left\">";
                            cout << "<h3 class=\"display-5\">" << car.getModel() << "</h3>";
                            cout << "<p class=\"fw-bold fs-4\">" << fixed << setprecision(2) << "₱" << car.getPrice() << "</p>";
                            cout << "<p class=\"lead\">" << car.getDescription() << "</p>";
                        cout << "</section>";
                        cout << "<section class=\"col-lg-8 d-flex align-items-center z-index\">";
                        cout << "<img src=\"" << car.getImageUrl() << "\" class=\"animate fade-right card-img\" alt=\"" << car.getModel() << "\">";
                        cout << "</section>";
                        cout << "<section class=\"card-circle animate fade-up bg-dark\"> </section>";
                    cout << "</a>";
            }
            cout << "</section>";
            cout << "</section>";
        }
    } else if (requestMethod == "POST") {
        string contentLengthStr = getenv("CONTENT_LENGTH");
        if (!contentLengthStr.empty()) {
            int contentLength = stoi(contentLengthStr);
            string postBody;
            postBody.resize(contentLength);
            cin.read(&postBody[0], contentLength);
            map<string, string> postParams = parseQueryString(postBody);
            if (postParams.find("model") != postParams.end()) {
                string modelTag = postParams["model"];
                bool found = false;
                for (const Car& car : carDatabase) {
                    if (toLower(car.getTag()).find(toLower(modelTag)) != string::npos) {
                        found = true;
                        cout << "<li><a href=\"?model=" << car.getTag() << "\">" << car.getModel() << "</a></li>";
                    }
                }
                if (!found) {
                    cout << modelNotFoundContent;
                }
            } else {
                cout << modelNotFoundContent;
            }
        } else {
            cout << "<h1>Electric Car Models</h1>";
            cout << "<form method=\"post\">";
            cout << "<label for=\"search\">Search:</label>";
            cout << "<input type=\"text\" id=\"search\" name=\"model\">";
            cout << "<input type=\"submit\" value=\"Submit\">";
            cout << "</form>";
            cout << "<ul>";
            for (const Car& car : carDatabase) {
                cout << "<li><a href=\"?model=" << car.getTag() << "\">" << car.getModel() << "</a></li>";
            }
            cout << "</ul>";
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
                                <a class="nav-link p-0 m-3 text-light" href="./faqs.cgi">FAQs</a>
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
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js"></script>
        <!-- Navbar Animation Script -->
        <script>
            const navbar = document.getElementById('navbar');

            window.addEventListener('resize', () => {
                if (window.innerWidth < 768) {
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
                    navbar.classList.remove('bg-dark');
                    navbar.classList.remove('border-darker');
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