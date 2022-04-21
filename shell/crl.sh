#!/bin/bash

CRL_LIST=/tmp/private.crl
CRL_TEXT=/tmp/private.crl.txt
CRL_CSV=/tmp/private.csv

DB_SERVER=<db server>
DB_USER=<db user>
DB_PASS=<db user password>
DB_DATABASE=<database name>

/usr/bin/curl http://crl.ermis.gov.gr/HPARCASign/LatestCRL.crl --output /tmp/private.crl 2>/dev/null
/usr/bin/openssl crl -inform DER -noout -text -in /tmp/private.crl -out $CRL_TEXT

/home/<username>/crl <$CRL_TEXT >$CRL_CSV

/usr/bin/scp $CRL_CSV $DB_SERVER:$CRL_CSV
/usr/bin/mysql -h $DB_SERVER -u$DB_USER -p$DB_PASS $DB_DATABASE -e 'TRUNCATE TABLE crl_cert'
/usr/bin/mysql -h $DB_SERVER -u$DB_USER -p$DB_PASS $DB_DATABASE -e 'REPLACE INTO crl VALUES (1, CURDATE())'
/usr/bin/mysql -h $DB_SERVER -u$DB_USER -p$DB_PASS $DB_DATABASE -e 'LOAD DATA LOCAL INFILE "$CRL_CSV" INTO TABLE crl_cert COLUMNS TERMINATED BY "," OPTIONALLY ENCLOSED BY "\"" ESCAPED BY "\\" LINES TERMINATED BY "\n"'
/usr/bin/mysql -h $DB_SERVER -u$DB_USER -p$DB_PASS $DB_DATABASE -e 'OPTIMIZE TABLE crl;OPTIMIZE TABLE crl_cert;' 2>/dev/null
