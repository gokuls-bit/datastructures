import React, { useState } from "react";
import "./AnimalFilterApp.css";

function AnimalFilterApp() {
  const [category, setCategory] = useState("Mammals");

  const animals = {
    Birds: ["Eagle", "Parrot", "Penguin"],
    Mammals: ["Lion", "Tiger", "Elephant"],
    Reptiles: ["Snake", "Crocodile", "Lizard"],
    Fish: ["Shark", "Salmon", "Goldfish"],
  };

  return (
    <div className="container">

      <div className="buttons">
        <button onClick={() => setCategory("Birds")}>
          Birds
        </button>

        <button onClick={() => setCategory("Mammals")}>
          Mammals
        </button>

        <button onClick={() => setCategory("Reptiles")}>
          Reptiles
        </button>

        <button onClick={() => setCategory("Fish")}>
          Fish
        </button>
      </div>

      <div className="cards">
        {animals[category].map((animal, index) => (
          <div className="card" key={index}>
            {animal}
          </div>
        ))}
      </div>

    </div>
  );
}

export default AnimalFilterApp;


