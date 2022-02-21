{-# LANGUAGE RankNTypes #-}
{-# LANGUAGE KindSignatures #-}
{-# LANGUAGE TypeOperators #-}

{-# LANGUAGE ConstraintKinds #-}

{-# LANGUAGE MultiParamTypeClasses #-}

{-# LANGUAGE FlexibleInstances #-}

module PolyClose where
  import Prelude()
  import NewPrelude
  import Demote
  import Data.Kind


  class Preserves (c :: * -> Constraint) (f :: * -> *)

  type Constrained (c :: * -> Constraint) (f :: * -> *) =
    forall a. c a => a -> f a

  type family Iterate (n :: ℕ) (f :: * -> *) a where
    Iterate Zero _ a = a
    Iterate (Succ n) f a = f (Iterate n f a)

  iterate :: forall
    (n :: ℕ)
    (c :: * -> Constraint)
    (f :: * -> *) a.
      (c a, Preserves c f) =>
        Constrained c -> a -> Iterate n f a
  iterate
