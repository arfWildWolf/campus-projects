document.addEventListener('DOMContentLoaded', function () {
    const categorySelect = document.getElementById('category');
    const productCards = document.querySelectorAll('.products .card');

    // Assign data-category attributes to each card for easier filtering
    productCards.forEach(card => {
        const title = card.querySelector('h3').textContent.trim();
        if (title.startsWith('Headphone')) {
            card.dataset.category = 'headphones';
        } else if (title.startsWith('Earbud')) {
            card.dataset.category = 'earbuds';
        } else if (title.startsWith('Speaker')) {
            card.dataset.category = 'speakers';
        } else if (title.startsWith('Open-Ear')) {
            card.dataset.category = 'open-ear';
        }
    });

    

    function filterProducts() {
        const selected = categorySelect.value;
        productCards.forEach(card => {
            const category = card.dataset.category;
            if (selected === 'all' || category === selected) {
                card.style.display = '';
            } else {
                card.style.display = 'none';
            }
        });
    }

    categorySelect.addEventListener('change', filterProducts);

    // Run filter on page load
    filterProducts();
});