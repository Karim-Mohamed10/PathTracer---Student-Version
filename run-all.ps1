$scenes = @(
    'tri_test0.0', 'tri_test0.1', 'tri_test1.0', 'tri_test1.1', 'tri_test2.0', 'tri_test2.1',  'tri_test3.0',  'tri_test3.1',
    'sph_test0.0', 'sph_test0.1', 'sph_test1.0', 'sph_test1.1', 'sph_test2.0', 'sph_test2.1',  'sph_test3.0',  'sph_test3.1',
    'balls0', 'balls1', 'balls2',
    'city0', 'city1', 'city2', 'city3',
    'cornell_box0', 'cornell_box1', 'cornell_box2', 'cornell_box3',
    # Change this item
    'yourfirstname_yourid'
)

New-Item -Path .\output -ItemType Directory -Force

foreach ($scene in $scenes) {
    & .\build\path-tracer.exe $scene -o .\output\$scene.png -s 1000 -b 5
}