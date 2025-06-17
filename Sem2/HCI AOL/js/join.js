document.addEventListener('DOMContentLoaded', function () {
    const form = document.getElementById('membershipForm');

    form.addEventListener('submit', function (e) {
        e.preventDefault();

        // Get form values
        const name = document.getElementById('name').value.trim();
        const email = document.getElementById('email').value.trim();
        const gender = document.getElementById('gender').value;
        const dob = document.getElementById('dob').value;
        const password = document.getElementById('password').value;
        const terms = document.getElementById('terms').checked;

        // Name validation: at least 2 characters
        if (name.length < 2) {
            alert('Name must be at least 2 characters.');
            return;
        }

        // Email validation: basic check without regex
        function isValidEmail(email) {
            if (!email) return false;
            const atIndex = email.indexOf('@');
            const dotIndex = email.lastIndexOf('.');
            // '@' must exist, not at start or end, only one '@'
            if (atIndex <= 0 || atIndex !== email.lastIndexOf('@') || atIndex === email.length - 1) return false;
            // '.' must exist after '@', not at end
            if (dotIndex < atIndex + 2 || dotIndex === email.length - 1) return false;
            return true;
        }
        if (!isValidEmail(email)) {
            alert('Please enter a valid email address.');
            return;
        }

        // Gender validation
        if (!gender) {
            alert('Please select your gender.');
            return;
        }

        // Date of Birth validation: must be in the past and user at least 13 years old
        if (!dob) {
            alert('Please enter your date of birth.');
            return;
        }
        const dobDate = new Date(dob);
        const today = new Date();
        if (dobDate >= today) {
            alert('Date of birth must be in the past.');
            return;
        }
        let age = today.getFullYear() - dobDate.getFullYear();
        const m = today.getMonth() - dobDate.getMonth();
        if (m < 0 || (m === 0 && today.getDate() < dobDate.getDate())) {
            age--;
        }
        if (age < 13) {
            alert('You must be at least 13 years old to join.');
            return;
        }

        // Password validation: at least 6 characters, contains a number (no regex)
        function hasNumber(str) {
            for (let i = 0; i < str.length; i++) {
                if (str[i] >= '0' && str[i] <= '9') return true;
            }
            return false;
        }
        if (password.length < 6 || !hasNumber(password)) {
            alert('Password must be at least 6 characters and contain a number.');
            return;
        }

        // Terms validation
        if (!terms) {
            alert('You must agree to the terms and conditions.');
            return;
        }

        // Success
        alert('Thank you for joining Noisecore, ' + name + '!');
        form.reset();
    });
});