# processCRL
Process Certificate Revocation List

The purpose of this project is to download the Certificate Revocation List from https://pki.ermis.gov.gr/repository.html
(the actual link is http://crl.ermis.gov.gr/HPARCASign/LatestCRL.crl)
and convert it to store the certifcate serial numbers and revocation date in a database for further usage.

We need to query the database for the date a certificate was revoked.
