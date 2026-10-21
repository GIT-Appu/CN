# SMTP Analysis

1. Use a permitted lab SMTP service or a local test server; do not expose real credentials.
2. Capture the mail transaction and filter with `smtp` or the service port.
3. Identify the server greeting, `EHLO`/`HELO`, sender, recipient, and data-transfer commands.
4. Record SMTP reply codes such as `220`, `250`, and `354`.
5. If TLS is negotiated, explain that the message body is encrypted after the TLS upgrade.
