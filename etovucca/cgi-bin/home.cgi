#!/bin/bash

render_home() {
    echo "Content-Type: text/html"
    echo ""
    echo ""
    echo "<link rel='stylesheet' href='https://spar.isi.jhu.edu/teaching/443/main.css'>"
    echo "<h2 id='dlobeid-etovucca-voting-machine'>DLOBEID EtovUcca Voting Machine</h2>"
    echo "<h1 id='home'>Home</h1><br>"
    echo "<ul>"
    echo "<li><a href='./register.cgi'>Register to Vote</a></li>"
    echo "<li><a href='./vote.cgi'>Vote for an Office</a></li>"
    echo "<li><a href='./login.cgi'>Administrator Interface (Requires Login)</a></li>"
    echo "</ul>"
}

render_home