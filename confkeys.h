confkey(model, integer, cycle, 20,
        seconds) confkey(model, boolean, usecorrelation, true,
                         -) confkey(model, integer, minsize, 2000000, bytes)
    confkey(model, integer, memtotal, -10, signed_integer_percent)
        confkey(model, integer, memfree, 50, signed_integer_percent)
            confkey(model, integer, memcached, 0, signed_integer_percent)
                confkey(system, boolean, doscan, true,
                        -) confkey(system, boolean, dopredict, true, -)
                    confkey(system, integer, autosave, 3600, seconds)
                        confkey(system, string_list, mapprefix, NULL, -)
                            confkey(system, string_list, exeprefix, NULL, -)
                                confkey(system, integer, maxprocs, 30,
                                        processes)
                                    confkey(system, enum, sortstrategy, 3, -)
