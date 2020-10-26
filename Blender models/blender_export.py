import bpy  



current_obj = bpy.context.active_object  
verts_local = [v.co for v in current_obj.data.vertices.values()]
verts_world = [current_obj.matrix_world @ v_local for v_local in verts_local]

file = open(bpy.path.abspath("//") + "output.txt", "w")

file.write(str(len(current_obj.data.polygons)) + "\n")

file.write("%.2f %.2f %.2f\n" % (current_obj.location.x, current_obj.location.y, current_obj.location.z))

for i, face in enumerate(current_obj.data.polygons):
    verts_indices = face.vertices[:]
    file.write(" ".join(["%.2f %.2f %.2f" % (verts_world[k].x, verts_world[k].z, verts_world[k].y) for k in verts_indices]))
    file.write("\n")