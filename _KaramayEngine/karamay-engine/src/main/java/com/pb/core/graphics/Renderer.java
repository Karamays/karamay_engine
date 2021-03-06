package com.pb.core.graphics;

import com.pb.core.graphics.buffer.AtomicCounterBuffer;
import com.pb.core.graphics.buffer.ElementArrayBuffer;
import com.pb.core.graphics.buffer.ShaderStorageBuffer;
import com.pb.core.graphics.buffer.UniformBuffer;
import com.pb.core.graphics.pipeline.Pipeline;
import com.pb.core.graphics.transformfeedback.TransformFeedback;
import com.pb.core.graphics.uniform.Uniform;
import com.pb.core.graphics.vertex.VertexArray;
import com.pb.core.graphics.vertex.VertexAttributeLayout;

import java.nio.ByteBuffer;
import java.util.ArrayList;

public class Renderer {


    public void construct()
    {
        ArrayList<String> shaderPaths = new ArrayList<>();
        shaderPaths.add("shaders/pbrmesh.vert");
        shaderPaths.add("shaders/pbrmesh.tesc");
        shaderPaths.add("shaders/pbrmesh.tese");
        shaderPaths.add("shaders/pbrmesh.geom");
        shaderPaths.add("shaders/pbrmesh.frag");

        ByteBuffer byteBuffer = ByteBuffer.allocate(100);
        byteBuffer.array();
        byteBuffer.capacity();

        VertexArray vertexArray
                = new VertexArray(new VertexAttributeLayout(), byteBuffer.array(), byteBuffer.capacity());

        ElementArrayBuffer elementArrayBuffer
                = new ElementArrayBuffer();

        TransformFeedback transformFeedback
                = new TransformFeedback();

        ArrayList<Uniform> uniforms = new ArrayList<>();
        ArrayList<UniformBuffer> uniformBuffers = new ArrayList<>();
        ArrayList<ShaderStorageBuffer> shaderStorageBuffers = new ArrayList<>();
        ArrayList<AtomicCounterBuffer> atomicCounterBuffers = new ArrayList<>();



        Pipeline pipeline = new Pipeline();
        pipeline.setShaders(shaderPaths)
                .setVertexArray(vertexArray)
                .setElementArrayBuffer(elementArrayBuffer)
                .setTransformFeedback(transformFeedback)
                .addUniforms(uniforms)
                .addUniformBuffers(uniformBuffers)
                .addShaderStorageBuffers(shaderStorageBuffers)
                .addAtomicCounterBuffers(atomicCounterBuffers)
                .setFramebuffer();

    }

}
