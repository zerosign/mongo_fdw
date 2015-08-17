#!/usr/bin/env python

APP_NAME = 'mongo_fdw'
VERSION  = '2.0'

def options(opt):
    opt.load('compiler_cxx')
    
def configure(ctx):
    ctx.load('compiler_cxx')

def build(bld):
    bld.shlib(
        lib=['pgcommon', 'pgport', 'pam', 'xml2', 'ssl', 'crypto', \
             'gssapi_krb5', 'z', 'readline', 'rt', 'crypt', 'dl', 'm'],
        target='mongo_fdw',
        source="""
        ./src/foreign_wrapper.cpp
        """,
    )

