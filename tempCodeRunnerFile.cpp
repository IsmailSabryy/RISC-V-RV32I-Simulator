cout << setw(20) << "REG" << setw(20) << "DEC" << setw(20) << "BIN" << setw(20) << "HEX" << endl;

                    for (const auto &linee : reg)
                    {
                        cout << setw(20) << linee.first << setw(20) << linee.second << setw(20) << "0b" << dectobinary(linee.second) << setw(20) << "0x" << dectohex(linee.second) << endl;
                    }