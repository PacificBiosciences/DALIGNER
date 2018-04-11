from ctypes import *

_READIDX = c_uint16
_TRACE_XOVR = 125

class DAZZ_READ(Structure):
    _fields_ = [ ("origin", c_int),
                 ("begin", _READIDX),
                 ("end", _READIDX),
                 ("boff", c_int64),
                 ("coff", c_int64),
                 ("flags", c_int)]


class DAZZ_TRACK(Structure):
    pass

DAZZ_TRACK._fields_ = [ ("_track", POINTER(DAZZ_TRACK)),
                        ("name", c_char_p),
                        ("size", c_int),
                        ("anno", c_void_p),
                        ("data", c_void_p)]


class DAZZ_DB(Structure):
    _fields_ = [ ( "oreads", c_int ),
                 ( "breads", c_int ),
                 ( "cutoff", c_int ),
                 ( "all", c_int),
                 ( "freq", c_float * 4),
                 ( "maxlen", c_int),
                 ( "totlen", c_int64),
                 ( "nreads", c_int),
                 ( "trimmed", c_int),
                 ( "part", c_int),
                 ( "ofirst", c_int),
                 ( "bfirst", c_int),
                 ( "path", c_char_p),
                 ( "loaded", c_int),
                 ( "bases", c_void_p),
                 ( "reads", POINTER(DAZZ_READ)),
                 ( "tracks", POINTER(DAZZ_TRACK)) ]


DB = CDLL("./DB.so")

libc = CDLL("libc.so.6")

fopen = libc.fopen
fclose = libc.fclose
fread = libc.fread
fread.argtypes = [c_void_p, c_size_t, c_size_t, c_void_p]

open_DB = DB.Open_DB
open_DB.argtypes = [c_char_p, POINTER(DAZZ_DB)]
open_DB.restype = c_int

load_read  = DB.Load_Read
load_read.argtypes = [POINTER(DAZZ_DB), c_int, c_char_p, c_int]
load_read.restype = c_int

close_DB = DB.Close_DB
close_DB.argtypes = [POINTER(DAZZ_DB)]
close_DB.restype = c_int

trim_DB = DB.Trim_DB
trim_DB.argtypes = [POINTER(DAZZ_DB)]
trim_DB.restype = c_int

new_read_buffer = DB.New_Read_Buffer
new_read_buffer.argtypes = [ POINTER(DAZZ_DB) ]
new_read_buffer.restype = POINTER(c_char)
