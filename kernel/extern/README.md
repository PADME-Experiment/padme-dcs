# External dependencies

The external dependencies shtould be solved by the user.
- V8100 SDK
- CAENHVWrapper


Here is how the directory tree should look like:

```
.
├── CAENHVWrapper
│   ├── CAENHVWrapper.h
│   ├── libcaenhvwrapper.so -> libcaenhvwrapper.so.5.82
│   └── libcaenhvwrapper.so.5.82
├── lib
│   ├── libcaenhvwrapper.so -> ../CAENHVWrapper/libcaenhvwrapper.so
│   └── libV8100SDK.so -> ../V8100/V8100SDK/x86_64/libV8100SDK.so
└── V8100
    ├── common
    │   ├── board_commons.h
    │   ├── common_defs.h
    │   └── com_phy_layer.h
    └── V8100SDK
        ├── V8100.h
        └── x86_64
            ├── libV8100SDK.so -> libV8100SDK.so.1.0
            └── libV8100SDK.so.1.0
```
