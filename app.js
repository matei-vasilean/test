const express = require("express");
const fs = require("fs");
const app = express();
const PORT = 3000;

const products = JSON.parse(fs.readFileSync("products.json"));

app.get("/search", (req, res) => {
    const { textToSearch, minimumPrice, maximumPrice } = req.query;
    var filteredProducts = products;

    if (filteredProducts)
        filteredProducts = products.filter(p => 
            p.name.toLowerCase().includes(textToSearch?.toLowerCase() || "")
        );

    if (minimumPrice)
        filteredProducts = filteredProducts.filter(p => p.price >= parseFloat(minimumPrice));

    if (maximumPrice)
        filteredProducts = filteredProducts.filter(p => p.price >= parseFloat(maximumPrice));

    const result = `
        <table border=1>
            <tr><th>Name</th><th>Price</th><th>Quantity</th></tr>
            ${filteredProducts.map(p => `<tr><td>${p.name}</td><td>${p.price}</td><td>${p.quantity}</td></tr>`).join("")}
        </table>
    `;

    res.send(result);
});

app.use(express.static("public"));

app.listen(PORT, () => console.log(`Server is running on port ${PORT}`));