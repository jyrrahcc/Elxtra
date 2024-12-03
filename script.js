// Function to decode URL-encoded strings
function urlDecode(str) {
    return decodeURIComponent(str.replace(/\+/g, ' '));
}

// Function to parse query string into a key-value object
function parseQueryString(query) {
    const params = {};
    const pairs = query.split('&');
    for (const pair of pairs) {
        const [key, value] = pair.split('=');
        if (key && value) {
            params[urlDecode(key)] = urlDecode(value);
        }
    }
    return params;
}

// Function to parse cookies into a key-value object
function parseCookies(cookieHeader) {
    const cookies = {};
    if (cookieHeader) {
        const pairs = cookieHeader.split('; ');
        for (const pair of pairs) {
            const [key, value] = pair.split('=');
            if (key && value) {
                cookies[key] = value;
            }
        }
    }
    return cookies;
}

// Main function to render user-specific content
function renderUserDisplay() {
    const cookies = parseCookies(document.cookie); // Parse cookies
    const userDisplayDiv = document.getElementById('user-display'); // Target div for user display

    if (cookies.name) {
        // If the user is logged in, show the dropdown menu
        userDisplayDiv.innerHTML = `
            <div class="d-flex align-items-center text-light gap-3">
                <div class="dropdown">
                    <button class="btn btn-outline-danger text-light fw-bold border-light dropdown-toggle" 
                            type="button" 
                            id="dropdownUser" 
                            data-bs-toggle="dropdown" 
                            aria-haspopup="true" 
                            aria-expanded="false">
                        ${cookies.name}
                    </button>
                    <div class="dropdown-menu dropdown-menu-end" aria-labelledby="dropdownUser">
                        <a class="dropdown-item" href="./carloancalculator.html">Car Loan Calculator</a>
                        <a class="dropdown-item" href="./userprofile.html">User Profile</a>
                        <a class="dropdown-item" href="./logout.html">Logout</a>
                    </div>
                </div>
            </div>
        `;
    } else {
        // If the user is not logged in, show the login button
        userDisplayDiv.innerHTML = `
            <a href="./login.html" class="btn btn-outline-danger text-light fw-bold border-light">Login</a>
        `;
    }
}

// Run the function on page load
window.onload = renderUserDisplay;

// Function to generate the welcome message
function getWelcomeMessage() {
    const cookies = parseCookies();
    const name = cookies.name; // Check if the "name" cookie exists
    return name 
        ? `<h2 class="display-3 text-light">Welcome, ${name}!</h2>` 
        : `<h2 class="display-3 text-light">Drive the Future with Elxtra Motors</h2>`;
}

// Function to render the welcome message on the page
function renderWelcomeMessage() {
    const welcomeDiv = document.getElementById('welcome-message');
    welcomeDiv.innerHTML = getWelcomeMessage();
}

// Run the render function when the page loads
window.onload = renderWelcomeMessage;