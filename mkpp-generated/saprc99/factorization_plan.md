# saprc99 Factorization Plan

| Block | First operation | Operations | Dependencies |
|---:|---:|---:|---|
| 0 | 0 | 256 | none |
| 1 | 256 | 256 | 0 |
| 2 | 512 | 256 | 0, 1 |
| 3 | 768 | 256 | 0, 1, 2 |
| 4 | 1024 | 256 | 0, 1, 2, 3 |
| 5 | 1280 | 256 | 0, 1, 2, 3, 4 |
| 6 | 1536 | 53 | 0, 1, 2, 3, 4, 5 |

The plan has 1589 numeric operations and 697 fill entries for 82 species.
