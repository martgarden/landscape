#include "geometry.hpp"

namespace marrow {
    bool Geometry::parseOBJ(const char *file_name, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec3> &out_normals, std::vector<glm::vec2> &out_tex_coords, std::vector<GLushort> &out_indices)
    {
        // I love lambda functions :-)
        auto error_msg = [file_name] {
            cout << "Failed to read OBJ file " << file_name << ", its format is not supported" << endl;
        };

        struct OBJTriangle
        {
            int v0, v1, v2;
            int n0, n1, n2;
            int t0, t1, t2;
        };

        // Prepare the arrays for the data from the file.
        std::vector<glm::vec3> raw_vertices;        raw_vertices.reserve(1000);
        std::vector<glm::vec3> raw_normals;            raw_normals.reserve(1000);
        std::vector<glm::vec2> raw_tex_coords;        raw_tex_coords.reserve(1000);
        std::vector<OBJTriangle> raw_triangles;        raw_triangles.reserve(1000);

        // Load OBJ file
        ifstream file(file_name);
        if (!file.is_open())
        {
            cout << "Cannot open OBJ file " << file_name << endl;
            return false;
        }

        while (!file.fail())
        {
            string prefix;
            file >> prefix;

            if (prefix == "v")
            {
                glm::vec3 v;
                file >> v.x >> v.y >> v.z;
                raw_vertices.push_back(v);
                file.ignore(numeric_limits<streamsize>::max(), '\n');        // Ignore the rest of the line
            }
            else if (prefix == "vt")
            {
                glm::vec2 vt;
                file >> vt.x >> vt.y;
                raw_tex_coords.push_back(vt);
                file.ignore(numeric_limits<streamsize>::max(), '\n');        // Ignore the rest of the line
            }
            else if (prefix == "vn")
            {
                glm::vec3 vn;
                file >> vn.x >> vn.y >> vn.z;
                raw_normals.push_back(vn);
                file.ignore(numeric_limits<streamsize>::max(), '\n');        // Ignore the rest of the line
            }
            else if (prefix == "f")
            {
                OBJTriangle t;
                char slash;

                // And now check whether the geometry is of a correct format (that it contains only triangles,
                // and all vertices have their position, normal, and texture coordinate set).
                
                // Read the first vertex
                file >> ws;        if (!isdigit(file.peek()))    {    error_msg();        return false;    }
                file >> t.v0;
                file >> ws;        if (file.peek() != '/')        {    error_msg();        return false;    }
                file >> slash;
                file >> ws;        if (!isdigit(file.peek()))    {    error_msg();        return false;    }
                file >> t.t0;
                file >> ws;        if (file.peek() != '/')        {    error_msg();        return false;    }
                file >> slash;
                file >> ws;        if (!isdigit(file.peek()))    {    error_msg();        return false;    }
                file >> t.n0;

                // Read the second vertex
                file >> ws;        if (!isdigit(file.peek()))    {    error_msg();        return false;    }
                file >> t.v1;
                file >> ws;        if (file.peek() != '/')        {    error_msg();        return false;    }
                file >> slash;
                file >> ws;        if (!isdigit(file.peek()))    {    error_msg();        return false;    }
                file >> t.t1;
                file >> ws;        if (file.peek() != '/')        {    error_msg();        return false;    }
                file >> slash;
                file >> ws;        if (!isdigit(file.peek()))    {    error_msg();        return false;    }
                file >> t.n1;

                // Read the third vertex
                file >> ws;        if (!isdigit(file.peek()))    {    error_msg();        return false;    }
                file >> t.v2;
                file >> ws;        if (file.peek() != '/')        {    error_msg();        return false;    }
                file >> slash;
                file >> ws;        if (!isdigit(file.peek()))    {    error_msg();        return false;    }
                file >> t.t2;
                file >> ws;        if (file.peek() != '/')        {    error_msg();        return false;    }
                file >> slash;
                file >> ws;        if (!isdigit(file.peek()))    {    error_msg();        return false;    }
                file >> t.n2;

                // Check that this polygon has only three vertices (we support triangles only).
                // It also skips all white spaces, effectively ignoring the rest of the line (if empty).
                file >> ws;        if (isdigit(file.peek()))    {    error_msg();        return false;    }

                // Subtract one, OBJ indexes from 1, not from 0
                t.v0--;        t.v1--;        t.v2--;
                t.n0--;        t.n1--;        t.n2--;
                t.t0--;        t.t1--;        t.t2--;

                raw_triangles.push_back(t);
            }
            else
            {
                // Ignore other cases
                file.ignore(numeric_limits<streamsize>::max(), '\n');        // Ignore the rest of the line
            }
        }
        file.close();

        // Indices in OBJ file cannot be used, we need to convert the geometry in a way we could draw it
        // with glDrawArrays.
        out_vertices.clear();        out_vertices.reserve(raw_triangles.size() * 3);
        out_normals.clear();        out_normals.reserve(raw_triangles.size() * 3);
        out_tex_coords.clear();        out_tex_coords.reserve(raw_triangles.size() * 3);
        out_indices.clear();         out_indices.reserve(raw_triangles.size() * 3);
        std::map<std::tuple<GLushort, GLushort, GLushort>, GLushort> unique;
        for (size_t i = 0; i < raw_triangles.size(); i++)
        {
            if ((raw_triangles[i].v0 >= int(raw_vertices.size())) ||
                (raw_triangles[i].v1 >= int(raw_vertices.size())) ||
                (raw_triangles[i].v2 >= int(raw_vertices.size())) ||
                (raw_triangles[i].n0 >= int(raw_normals.size())) ||
                (raw_triangles[i].n1 >= int(raw_normals.size())) ||
                (raw_triangles[i].n2 >= int(raw_normals.size())) ||
                (raw_triangles[i].t0 >= int(raw_tex_coords.size())) ||
                (raw_triangles[i].t1 >= int(raw_tex_coords.size())) ||
                (raw_triangles[i].t2 >= int(raw_tex_coords.size())))
            {
                // Invalid out-of-range indices
                error_msg();
                return false;
            }
            GLushort v0, v1, v2;
            auto it = unique.find(std::tuple<GLushort, GLushort, GLushort>(raw_triangles[i].v0, raw_triangles[i].n0, raw_triangles[i].t0));
            if(it0 == unique.end()) {
                out_vertices.push_back(raw_vertices[raw_triangles[i].v0]);
                out_normals.push_back(raw_normals[raw_triangles[i].n0]);
                out_tex_coords.push_back(raw_tex_coords[raw_triangles[i].t0]);
                unique[std::tuple<GLushort, GLushort, GLushort>(raw_triangles[i].v0, raw_triangles[i].n0, raw_triangles[i].t0)] = out_vertices.size() - 1;
                v0 = out_vertices.size() - 1;
            }
            else {
                v0 = *it;
            }
            it = unique.find(std::tuple<GLushort, GLushort, GLushort>(raw_triangles[i].v1, raw_triangles[i].n1, raw_triangles[i].t1));
            if(it1 == unique.end()) {
                out_vertices.push_back(raw_vertices[raw_triangles[i].v1]);
                out_normals.push_back(raw_normals[raw_triangles[i].n1]);
                out_tex_coords.push_back(raw_tex_coords[raw_triangles[i].t1]);
                unique[std::tuple<GLushort, GLushort, GLushort>(raw_triangles[i].v1, raw_triangles[i].n1, raw_triangles[i].t1)] = out_vertices.size() - 1;
                v1 = out_vertices.size() - 1;
            }
            else {
                v1 = *it;
            }
            it = unique.find(std::tuple<GLushort, GLushort, GLushort>(raw_triangles[i].v2, raw_triangles[i].n2, raw_triangles[i].t2));
            if(it2 == unique.end()) {
                out_vertices.push_back(raw_vertices[raw_triangles[i].v2]);
                out_normals.push_back(raw_normals[raw_triangles[i].n2]);
                out_tex_coords.push_back(raw_tex_coords[raw_triangles[i].t2]);
                unique[std::tuple<GLushort, GLushort, GLushort>(raw_triangles[i].v2, raw_triangles[i].n2, raw_triangles[i].t2)] = out_vertices.size() - 1;
                v2 = out_vertices.size() - 1;
            }
            else {
                v2 = *it;
            }

            out_indices.push_back(v0);
            out_indices.push_back(v1);
            out_indices.push_back(v2);
        }

        return true;
    }
}
