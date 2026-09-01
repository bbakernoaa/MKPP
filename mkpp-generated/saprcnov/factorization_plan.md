# saprcnov Factorization Plan

| Block | First operation | Operations | Dependencies |
|---:|---:|---:|---|
| 0 | 0 | 256 | none |
| 1 | 256 | 256 | 0 |
| 2 | 512 | 256 | 0, 1 |
| 3 | 768 | 256 | 0, 1, 2 |
| 4 | 1024 | 256 | 0, 1, 2, 3 |
| 5 | 1280 | 123 | 0, 1, 2, 3, 4 |

The plan has 1403 numeric operations and 596 fill entries for 96 species.
