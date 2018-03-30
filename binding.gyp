{
    "targets": [{
        "target_name": "native",
        "conditions": [
            [
                'OS=="mac"', {
                    "sources": [ "./src/module_mac.m" ],
                    "libraries": [ "-framework Cocoa" ]
                },
                'OS=="win"', {
                    "sources": [ "./src/module_win.c" ],
                    "libraries": ["user32.lib"]
                },
                # default
                {
                    "sources": [ "./src/module_linux.c" ],
                    'cflags': [
                        '<!@(<(pkg-config) --cflags x11)',
                    ],
                    'ldflags': [
                        '<!@(<(pkg-config) --libs-only-L --libs-only-other x11)',
                    ],
                    'libraries': [
                        '<!@(<(pkg-config) --libs-only-l x11)',
                    ],
                }
            ]
        ]
    }]
}