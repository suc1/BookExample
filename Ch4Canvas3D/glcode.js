Qt.include("three.js")

var camera, scene, renderer;
var cube;

function initializeGL(canvas) {
    scene = new THREE.Scene();
    camera = new THREE.PerspectiveCamera(75, canvas.width / canvas.height, 0.1, 1000);
    camera.position.z = 5;

    var directionalLight = new THREE.DirectionalLight(0xffffff);
    directionalLight.position.set(1, 1, 1).normalize();
    scene.add(directionalLight);

    var texture = THREE.ImageUtils.loadTexture('bricks.jpg');
    var material = new THREE.MeshBasicMaterial({ map: texture });
    var cubeGeometry = new THREE.BoxGeometry(3, 3, 3);

    var material = new THREE.MeshBasicMaterial({ color: 0x80c342,
                                                   shading: THREE.SmoothShading });
    var cubeGeometry = new THREE.BoxGeometry(1, 1, 1);
    cube = new THREE.Mesh(cubeGeometry, material);
    cube.rotation.set(0.785, 0.785, 0.0);
    scene.add(cube);

    renderer = new THREE.Canvas3DRenderer(
                { canvas: canvas, antialias: true, devicePixelRatio: canvas.devicePixelRatio });
    renderer.setSize(canvas.width, canvas.height);
}

function resizeGL(canvas) {
    camera.aspect = canvas.width / canvas.height;
    camera.updateProjectionMatrix();

    renderer.setPixelRatio(canvas.devicePixelRatio);
    renderer.setSize(canvas.width, canvas.height);
}

function paintGL(canvas) {
    cube.rotation.y -= 0.005;
    renderer.render(scene, camera);
}
