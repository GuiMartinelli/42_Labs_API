#!/bin/bash

curl -X POST --data "grant_type=client_credentials&client_id=c035ebabf61f708d9b3078f39431493174e6a3636e96060efe533627b24a3709&client_secret=a0c4e13c14ea1735068385c3d6127df03ef53f16d61e9a67c776a30d881ae7ce" https://api.intra.42.fr/oauth/token | cut -c 18- > src/token/token.txt