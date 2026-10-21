# DNS Analysis

1. Start capture, then resolve a new domain (for example, run `nslookup example.com`).
2. Filter with `dns`.
3. Match the query and response using the transaction ID.
4. Record query type, queried name, returned records, response code, and TTL.
5. Observe whether UDP port 53 is used; explain any TCP fallback if present.
